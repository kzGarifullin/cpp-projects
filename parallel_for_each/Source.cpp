#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

#include<iostream>
#include<chrono>

#include<algorithm>

#include <random>

#include <functional>




template < typename Iterator, typename T >
void parallel_for_each(Iterator first, Iterator last, T init)
{
	const std::size_t length = std::distance(first, last);

	const std::size_t max_size = 25;

	if (length <=  max_size)
	{
		std::for_each(first, last, init);
	}
	else
	{
		Iterator middle = first;
		std::advance(middle, length / 2);

		std::future < void> first_half_result =
			std::async(parallel_for_each < Iterator, T >, first, middle, init);

		

		first_half_result.get();
		parallel_for_each(middle, last, init);
	}
}

int main(int argc, char** argv)
{
	
	
	std::vector < int > v(1000000);

	std::iota(v.begin(), v.end(), 1);
	
	std::vector<int> nums{ 3, 4, 2, 8, 15, 267 };

	//Timer T;
	//std::for_each(nums.begin(), nums.end(), [](int& n) { n++; });
	//std::for_each(std::begin(vector), std::end(vector), [](auto x) {std::cout << x << " "; });
	//std::for_each(nums.begin(), nums.end(), [](auto x) {std::cout << x*1.34 << " "; });
	//std::for_each  (v.begin(), v.end(), [](auto x) {std::cout << x << " "; });
	parallel_for_each(v.begin(), v.end(), [](auto x) {std::cout << x << " "; });
	//std::for_each(v.begin(), v.end(), [](auto x) {return x * 3.12; });
	//parallel_for_each(v.begin(), v.end(), [](auto x) {return x*3.12; });
	//std::cout << parallel_for_each(nums.begin(), nums.end(), [](int& n) { n++; }) << std::endl;


	return EXIT_SUCCESS;
}