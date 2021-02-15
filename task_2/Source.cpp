#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>
#include<array>
#include<deque>
#include <list>
#include <forward_list>
class Timer
{
public:
	using clock_t = std::chrono::steady_clock;
	using time_point_t = clock_t::time_point;
	void pause() // определяем функцию-член
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
	
		
	//	std::vector<int>v;
	//	v.reserve(100000);
	//	for (auto i = 100000; i >= 0; --i)
	//	{
	//		v.push_back(i);
	//	}
	//Timer T;
	//std::sort(std::begin(v), std::end(v));//vector=100000
	
	/*std::array<int, 100001> myarray;
	int k = 0;
	for (auto i = 100000; i >= 0; --i)
	{
		myarray[k] = i;
		k++;
	}
	std::sort(myarray.begin(), myarray.end());//140000
	*/

	//std::deque<int> d ;
	//for (auto i = 100000; i >= 0; --i)
	//{
	//	d.push_back(i);
	//}
	//Timer T;
	//std::sort(std::begin(d), std::end(d));//477000


	//std::list<int> l;
	//for (auto i = 100000; i >= 0; --i)
	//{
	//	l.push_back(i);
	//}
	//Timer T;
	//l.sort();//60000
	
	std::forward_list<int> fl;
	int k = 0;
	for (auto i = 0; i <= 100000; ++i)
	{
		fl.push_front(i);
	}
	Timer T;
	fl.sort();//70000
	
}