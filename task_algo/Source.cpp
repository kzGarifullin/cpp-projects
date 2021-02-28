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


int main(int argc, char** argv)
{
	std::vector < std::string > vector;

	std::copy(
		std::istream_iterator < std::string >(std::cin),
		std::istream_iterator < std::string >(),
		std::back_inserter(vector));
	std::mt19937 g;
	//std::sort(vector.begin(), vector.end());
	std::shuffle(vector.begin(), vector.end(),g);
	std::sort(vector.begin(), vector.end());
	std::unique_copy(vector.cbegin(), vector.cend(),
		std::ostream_iterator < std::string >(std::cout, "\n"));
	std::shuffle(vector.begin(), vector.end(), g);
	std::cout << std::endl;
	std::copy(vector.cbegin(), vector.cend(),
		std::ostream_iterator < std::string >(std::cout, "\n"));

	system("pause");

	return EXIT_SUCCESS;
}