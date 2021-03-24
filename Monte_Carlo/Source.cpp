#include<iostream>
#include <random>
#include <math.h>
#include <thread>
#include <vector>
#include <functional>
void posl_pi(int N,double &local) {
	double x, y;
	int U = 0;
	double M = 0.0;
	std::mt19937_64 mt;
	std::uniform_real_distribution<>urd(0.0, 1.0);
	for (auto i = 0; i < N; ++i)
	{
		x = urd(mt);
		y = urd(mt);
		U++;
		if (pow((x - 0.5), 2) + pow((y - 0.5), 2) < 0.25)
		{
			M++;
		}
	}
	local+=  M;
}
int main() 
{
	int N = 10000000;
	double local = 0;
	posl_pi(N, local);
	std::cout << 4 * local / N<<std::endl;
	
	double local2 = 0;
	std::vector < std::thread > threads;
	
	for (std::size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
		{
			threads.push_back(std::thread (posl_pi,N, std::ref(local2)));
		}
	std::for_each(threads.begin(), threads.end(),
		std::mem_fn(&std::thread::join));
	
	std::cout << 4*local2 / N/ std::thread::hardware_concurrency();


}