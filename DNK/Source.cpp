#include <algorithm>
#include <atomic>
#include <future>
#include <iostream>
#include <iterator>
#include <numeric>
#include <thread>
#include <vector>
#include <string>

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
	void operator()(Iterator first, Iterator last, std::string element,
		std::promise < Iterator >& result, std::atomic < bool >& flag) noexcept
	{
		try
		{
			int count = 0;
			auto size = element.length();
			//auto j = 0;
			for (; (first != last) && !flag.load(); ++first)
			{
				//std::string first_str(*first);
				
				
				
					
					//auto k = element[j].c_str();
					if (*first == element[count])
					{
						count++;
						
					}
					else 
					{ 
						count = 0;
						if (*first == element[count])
						{
							count++;

						}
					
					}
					if (count == size)
					{
						result.set_value(first);
						flag.store(true);
						return;
					}


				

				/*if (*first == element)
				{
					result.set_value(first);
					flag.store(true);
					return;
				}*/
			}
		}
		catch (...)
		{
			try
			{
				result.set_exception(std::current_exception());
				flag.store(true);
			}
			catch (...)
			{
				// ...
			}
		}
	}
};

template < typename Iterator, typename T >
Iterator parallel_find(Iterator first, Iterator last, T element)
{
	const std::size_t length = std::distance(first, last);

	if (!length)
		return last;

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

			threads[i] = std::thread(Searcher < Iterator, T >(),
				block_start, block_end, element, std::ref(result), std::ref(flag));

			block_start = block_end;
		}

		Searcher < Iterator, T >()(block_start, last, element, result, flag);
	}

	if (!flag.load())
	{
		return last;
	}

	return result.get_future().get();
}

int main(int argc, char** argv)
{
	std::vector < int > v{ 1,4,2,6,8,9,7,9,3 };

	

	std::string s = "AGTCAGTCCCAGAAATACAGTA";
	std::string s1 = "CAG";
	std::vector<int> v1;
	auto result = parallel_find(s.begin(), s.end(), s1);
	v1.push_back(result - s.begin() - s1.length() + 1);
	if (result != s.end())
	{
		//std::cout << "Elements found: " << result - s.begin()-s1.length()+1<< std::endl;
		auto iter = result;
		while (iter < s.end()) {
			/*Iterator block_end = block_start;
			std::advance(block_end, block_size);*/
			
			std::advance(iter, 1);
			auto result = parallel_find(iter, s.end(), s1);
			
			if (result != s.end())
			{
				//std::cout << "Elements found: " << result - s.begin() - s1.length() + 1 << std::endl;
				v1.push_back(result - s.begin() - s1.length() + 1);
				iter = result;
			}
		}
	}
	else
	{
		std::cout << "Element not found." << std::endl;
	}
	std::for_each(v1.begin(), v1.end(), [](auto x) {std::cout << x << " "; });
	system("pause");

	return EXIT_SUCCESS;
}

//int main() 
//{
//	std::string s = "AGTCAGTCCCAGGTG";
//	std::string element = "CAG";
//	auto size = element.length();
//	int count = 0;
//	auto k = s.begin();
//	if (*k == s[1])
//		std::cout << "UYGF";
//
//}