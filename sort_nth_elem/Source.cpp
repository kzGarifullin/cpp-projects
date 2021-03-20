#include <numeric>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <random>
#include <chrono>
int main(int argc, char** argv)
{
	int N = 5000000;
	srand(4541);
	std::vector <int> vec1;
	std::vector<int> vec2;
	for (int count = 0; count < N; ++count)
	{
		auto a = rand();
		vec1.push_back(a);
		vec2.push_back(a);

	}
	std::cout << "sort" << std::endl;
	int count1 = 0;
	std::sort(std::begin(vec1), std::end(vec1), [&count1](auto x, auto y) {count1++; return x > y; });
	//std::for_each(std::begin(vec1), std::end(vec1), [](auto x) {std::cout << x << " "; });
	std::cout <<"count1 "<<count1<< std::endl;

	std::cout << "nth_element" << std::endl;
	int count2 = 0;
	std::nth_element(std::begin(vec2), std::next(std::begin(vec2), 10), std::end(vec2), [&count2](auto x, auto y) {count2++; return x > y; });
	//std::for_each(std::begin(vec2), std::end(vec2), [](auto x) {std::cout << x << " "; });
	std::cout << "count2 "<<count2<<std::endl;

}