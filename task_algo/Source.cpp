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

#include <algorithm>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <random>
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
	
	std::cout << "Prime numbers";
	std::for_each(std::begin(vector), std::end(vector), [](auto x) {if(isPrime(x))std::cout << x<<" "; });
	system("pause");

	return EXIT_SUCCESS;
}