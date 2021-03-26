#include<iostream>
#include<vector>

#include <future>
#include <numeric>
#include <thread>
#include<chrono>
#include<algorithm>
#include <random>
#include <functional>
#include <execution>
#include <numeric>
#include <cmath>
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

int main() {
	/*
	std::vector < int > v(1000000);

	std::iota(v.begin(), v.end(), 1);

	std::vector<int> nums{ 3, 4, 2, 8, 15, 267 };

	

	std::for_each(std::execution::par,v.begin(), v.end(), [](auto x) { return x * 3.12; });*/
	//par vers v 5-6 raz bistree posl version
	
	



	
	
	//std::vector<int> a{ 0, 1, 2, 3, 4 };
	//std::vector<int> b{ 5, 4, 2, 3, 1 };
	//for (int i = 1; i < 10000000; i++) {
	//	a.push_back(a[i] % i);
	//	b.push_back(a[i] % i+6);
	//
	//}
	//Timer T;
	//int r1 = std::inner_product(a.begin(), a.end(), b.begin(), 0);//posl
	//std::cout << "Inner product of a and b: " << r1 << '\n';
	//double result = std::transform_reduce(//parall
	//	std::execution::par,
	//	a.begin(), a.end(),
	//	b.begin(), 0.0
	//);
	//std::cout << result << '\n';
	
	//posl version v 3 raza bistree pri malenkih dannih N=1000
	//pri N=1000000 posl rabotaet za 40000 micro a par za 10000, par v 4 raza bistree
	//pri N=10000000  par spravilsa za 40000 a posl za 600000, to est parall bistree pri bolshih dannih v 15 raz
	
	




	std::vector<int> v(100000000,2); // or std::vector<int>v(10, 2);

	Timer T;
	
	/*std::partial_sum( v.begin(), v.end(), v.begin(),
		[](auto x, auto y) {return sin(x) + sin(y); });
	std::cout << '\n';*/
	
	


	std::cout << "exclusive sum: ";
	std::inclusive_scan(std::execution::par, v.begin(), v.end(),v.begin(),
		[](auto x,auto y){return sin(x)+sin(y);},//N=1000000 parall v 1.5 raza bistree
		2);

}