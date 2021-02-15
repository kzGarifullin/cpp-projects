#include<iostream>
#include<chrono>
#include<vector>
#include<algorithm>

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
	std::vector<int>v;
	std::vector<int>b;
	std::vector<int>c;
	v.reserve(100000);
	b.reserve(100000);
	c.reserve(100000);
	for (auto i = 100000; i >= 0; --i)
	{
		v.push_back(i);
		b.push_back(i);
		c.push_back(i);
	}
	Timer T;
	std::sort(std::begin(v), std::end(v));
	T.pause();
	std::sort(std::begin(b), std::end(b));
	T.cont();
	std::sort(std::begin(c), std::end(c));
}