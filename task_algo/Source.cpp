//#include<iostream>
//#include<vector>
//#include <iterator>     // std::back_inserter
//#include <algorithm>    // std::copy
//
//int main() {
//	std::vector<int>v1{ 1,2,3,4,5,6,7,8,9,10 };
//	int a;
//	for (int i = 1; i <= 5; i++)
//	{
//		std::cin >> a;
//		std::back_inserter();
//	}
//}
#include <numeric>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <random>
#include <chrono>
bool isPrime(int num) {
	bool flag = true;
	for (int i = 2; i <= num / 2; i++) {
		if (num % i == 0) {
			flag = false;
			break;
		}
	}
	return flag;
}

int main(int argc, char** argv)
{
	//std::vector < std::string > vector;
	std::vector<int>vector{ 1,2,3,4,5,6,7,8,9,10,11 };//#1
	
	
	//std::copy(
	//	std::istream_iterator < int >(std::cin),//#2
	//	std::istream_iterator < int >(),
	//	std::back_inserter(vector));


	std::mt19937 g;
	//std::sort(vector.begin(), vector.end());
	std::cout << "shuffle"<<std::endl;
	std::shuffle(vector.begin(), vector.end(),g);//#3
	std::copy(vector.cbegin(), vector.cend(),
	std::ostream_iterator < int >(std::cout, "\n"));
	std::sort(vector.begin(), vector.end());
	std::cout << "unique"<<std::endl;
	std::unique_copy(vector.cbegin(), vector.cend(),//#4
		std::ostream_iterator < int >(std::cout, "\n"));
	
	std::cout << std::endl;
	
	std::cout << "amount of odd numbers: "<<std::count_if(std::begin(vector), 
		std::end(vector), [](auto x) {return x % 2; })<<std::endl;//#5
	auto [min, max] = std::minmax_element(std::begin(vector),std::end(vector));
	std::cout << "min: "<<*min<<". max: "<<*max << std::endl;//#6
	
	std::cout << "Prime numbers: ";//#7
	std::for_each(std::begin(vector), std::end(vector), [](auto x) {if(isPrime(x))std::cout << x<<" "; });

	std::transform(std::begin(vector), std::end(vector), std::begin(vector), [](auto x) {return x * x; });
	std::cout << std::endl;
	std::cout << "Quadratic numbers: ";
	std::for_each(std::begin(vector), std::end(vector), [](auto x) {std::cout << x << " "; });//#8
	std::cout << std::endl;

	std::default_random_engine dre(std::chrono::system_clock::now().time_since_epoch().count());//#9
	std::vector<int>v2;

	std::uniform_int_distribution<>uid(1, 10);
	std::generate_n(std::back_inserter(v2), std::size(vector), [&dre, &uid]() {return uid(dre); });
	std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << " "; });//#9
	std::cout << std::endl;
	
	std::cout <<"summ: "<< std::accumulate(std::begin(v2), std::end(v2), 0)<<std::endl;//#10
	
	std::fill_n(std::begin(v2), 3, 1);
	std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << " "; });//#11
	std::cout << std::endl;

	std::vector<int> v3;//#12
	std::transform(std::begin(vector), std::end(vector), std::begin(v2),std::back_inserter(v3), [](auto a,auto b) {return a-b; });
	std::cout << "v3: " << std::endl;
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;

	std::for_each(std::begin(v3), std::end(v3), [](auto &x) {if (x < 30) x = 0; });//#13
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;
	
	v3.erase(std::remove_if(std::begin(v3), std::end(v3), [](auto x) {return x == 0; }), std::end(v3));
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;//#14
	

	std::cout << "15 task"<<std::endl;
	std::reverse(std::begin(v3), std::end(v3));//#15
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;
	
	std::cout << "16 task" << std::endl;
	std::nth_element(std::begin(v3), std::next(std::begin(v3), 3), std::end(v3), std::greater<int>());
	std::for_each(std::begin(v3), std::end(v3), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;

	std::cout << "17 task" << std::endl;
	std::sort(std::begin(v2), std::end(v2));
	std::sort(std::begin(vector), std::end(vector));
	std::for_each(std::begin(v2), std::end(v2), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;
	std::for_each(std::begin(vector), std::end(vector), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;


	std::cout << "18 task" << std::endl;
	std::vector<int> v4;
	std::merge(vector.begin(), vector.end(), v2.begin(), v2.end(),std::back_inserter(v4));
	std::for_each(std::begin(v4), std::end(v4), [](auto x) {std::cout << x << " "; });
	std::cout << std::endl;
	

	std::cout << "19 task" << std::endl;
	auto a=std::distance(std::begin(v4), std::find(v4.begin(), v4.end(), 1));
	auto b=std::distance(std::begin(v4), std::upper_bound(v4.begin(), v4.end(), 1));
	//std::cout<<std::binary_search(v4.begin(), v4.end(), 65);
	std::cout << "[" << a << "," << b << "]" << std::endl;

	std::cout << "20 task" << std::endl;

	return EXIT_SUCCESS;

}