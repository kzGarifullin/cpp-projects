#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>
#include <string>


std::mutex m_mutex;

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
struct Searcher
{
	void operator()(Iterator first, Iterator last, T element, std::vector<std::string::iterator>& v) noexcept
	{
		try
		{
			auto it = last;
			it = std::prev(it, size(element));
			for (auto i = first; i < it; ++i)
			{
				int k = 0;
					bool flag = true;
					auto it2 = i;
					std::advance(it2, size(element));
					auto j = i;
					for (j; j < it2; ++j)
					{
						
						if (*j == element[k])
						{
							k++;
						}
						else
						{
							flag = false;
							k = 0;
							break;
						}

					}
				std::lock_guard<std::mutex> lock(m_mutex);
				if (flag == true)
				{
					v.push_back(i);
				}

			}
		}
		catch (...)
		{

		}
	}
	
};

template < typename Iterator, typename T >
void parallel_find(Iterator first, Iterator last, T element,  std::vector<std::string::iterator> &v)
{
	const std::size_t length = std::distance(first, last);
	const std::size_t min_per_thread = 25;
	const std::size_t max_threads =
		(length + min_per_thread - 1) / min_per_thread;

	const std::size_t hardware_threads =
		std::thread::hardware_concurrency();

	const std::size_t num_threads =
		std::min(hardware_threads != 0 ? hardware_threads : 2, max_threads);

	const std::size_t block_size = length / num_threads;

	std::promise < Iterator > result;
	std::atomic < bool > flag(false);
	std::vector < std::thread > threads(num_threads - 1);

	{
		Threads_Guard guard(threads);

		Iterator block_start = first;

		for (std::size_t i = 0; i < (num_threads - 1); ++i)
		{
			Iterator block_end = block_start;
			std::advance(block_end, block_size);
			Iterator new_end = block_end;
			std::advance(new_end, size(element));//ZAHLEST
			threads[i] = std::thread(Searcher < Iterator, T >(),
				block_start, new_end, element, std::ref(v));

			block_start = block_end;
		}

		Searcher < Iterator, T >()(block_start, last, element, std::ref(v));
	}


}


int main(int argc, char** argv)
{
	std::vector < std::string::iterator > v;

	

	//std::string s = "AGTCACAGTAAAATATATATTATATCAGTATCAGATAAAAAAAAATATCAGATAACAAAAACAAAATCATT";
	std::string s = "CACACACACACACACACACACACACACACACACACACACACACACACA";

	std::string s1 = "CA";
	std::vector<std::string::iterator> v1;

	parallel_find(s.begin(), s.end(), s1, std::ref(v));
	//std::for_each(v.begin(), v.end(), [s](auto x) {std::cout << std::distance(x,s.begin()) << " "; });
	for (int i = 0; i < size(v); i++) {
		std::cout << std::distance(s.begin(), v[i]) << std::endl;
	}
	std::cout << std::endl;
	
	system("pause");

	return EXIT_SUCCESS;
}
