#include <iostream>
#include <set>
#include<vector>
#include <iostream>
#include <cstdlib> 
#include <algorithm>
#include <functional>
#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include <array>

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
int main()
{
	int N = 100000;
	srand(4541);
	std::vector <int> vec;
	std::set < int > set;
	std::vector<int> rand_vec;
	std::array<int, 100000> arr;

	for (int count = 0; count < N; ++count)
	{
		rand_vec.push_back(rand());
	}
	
	{Timer T;
	std::cout << "set " ;
	for (int count = 0; count < N; ++count)
	{
		set.insert(rand_vec[count]);
	}
	}
	{Timer T; std::cout << "vector ";
	for (int count = 0; count < N; ++count)
	{
		vec.push_back(rand_vec[count]);
	}
	std::sort(vec.begin(), vec.end());
	}
	
	{Timer T; std::cout << "array ";
	for (int count = 0; count < N; ++count)
	{
		arr[count] = rand_vec[count];
	}
	std::sort(arr.begin(), arr.end());
	}
//как видно array и vector в 2-3 раза быстрее set. N при котором сменяется лидер не существует
}