#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>
#include<chrono>


class Threads_Guard
{
public:

	explicit Threads_Guard(std::vector < std::thread >& threads) :
		m_threads(threads)
	{}

	Threads_Guard(Threads_Guard const&) = delete;

	Threads_Guard& operator=(Threads_Guard const&) = delete;

	~Threads_Guard() noexcept
	{
		try
		{
			for (std::size_t i = 0; i < m_threads.size(); ++i)
			{
				if (m_threads[i].joinable())
				{
					m_threads[i].join();
				}
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::vector < std::thread >& m_threads;
};

template < typename Iterator, typename T >
struct accumulate_block
{
	T operator()(Iterator first, Iterator last)
	{
		return std::accumulate(first, last, T());
	}
};

template < typename Iterator, typename T >
T parallel_accumulate(Iterator first, Iterator last, T init, int num)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return init;

	const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		num;

	const std::size_t block_size = length / num_threads;

	std::vector < std::future < T > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);

	Threads_Guard guard(threads);

	Iterator block_start = first;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		Iterator block_end = block_start;
		std::advance(block_end, block_size);

		std::packaged_task < T(Iterator, Iterator) > task{
			accumulate_block < Iterator, T >() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), block_start, block_end);

		block_start = block_end;
	}

	T last_result = accumulate_block < Iterator, T >()(block_start, last);

	T result = init;

	for (std::size_t i = 0; i < (num_threads - 1); ++i)
	{
		result += futures[i].get();
	}

	result += last_result;

	return result;
}




class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	void pause() 
	{
		pa = clock_t::now();
		dur += std::chrono::duration_cast<std::chrono::microseconds>(
			pa - m_begin);
	}
	void cont()
	{
		m_begin = clock_t::now();
	}
	Timer() : m_begin(clock_t::now()), dur(0) {}
	~Timer()
	{
		auto end = clock_t::now();
		std::cout << "micro: " << std::chrono::duration_cast<std::chrono::microseconds>(
			end - m_begin).count() + dur.count() << std::endl;
	}
private:
	time_point_t m_begin;
	time_point_t pa;
	std::chrono::microseconds dur;
};
//int main()
//{
//	std::vector<int>v;
//	std::vector<int>b;
//	std::vector<int>c;
//	v.reserve(100000);
//	b.reserve(100000);
//	c.reserve(100000);
//	for (auto i = 100000; i >= 0; --i)
//	{
//		v.push_back(i);
//		b.push_back(i);
//		c.push_back(i);
//	}
//	Timer T;
//	std::sort(std::begin(v), std::end(v));
//	T.pause();
//	std::sort(std::begin(b), std::end(b));
//	T.cont();
//	std::sort(std::begin(c), std::end(c));
//}
int main(int argc, char** argv)
{
	std::vector < int > v(100000000);

	std::iota(v.begin(), v.end(), 1);
	Timer T;
	std::cout << parallel_accumulate(v.begin(), v.end(), 0,640) << std::endl;


	return EXIT_SUCCESS;
}