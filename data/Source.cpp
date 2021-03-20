#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
int main(int argc, char** argv)
{
	std::string data = "5:46 1934/2a/10 1843!/5/3 13:67 14:59 42/ 24:59 34:56 20/03/2021 44/03/2021 26/08/2019! 23:45 12/14/2003 2021/03/20 2001/2/24  winner!@mail.ru 1994/5/3 reth!2ka.mi_tl@mail.ru dgh ta_ir465@yahoo.com ta_ir465@ ivanM@gmail.com q124 3434 masha_super_hero@phystech.edu  e77 2ka.mi_tl@mail.ru kukuha21,23@js.rer kukuha21,23@js!rer kivi@mail.ru ey jhjfjgf@mail.ru ";
    std::regex pattern(R"([0-9]{4}[/](([0][0-9])|([1][0-2])|[0-9])[/](([1-2][0-9])|([3][0-1])|[0-9]))");
	std::regex pattern2(R"((([0][0-9])|([1][0-9])|([2][0-4])|[0-9])[:](([0-5][0-9])|([0-9])))");
	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;
	std::string s("this subject has a submarine as a subsequence");
	std::for_each(begin, end, [](const std::smatch& m)
		{
			std::cout << m[0] << std::endl;
		});
	std::sregex_iterator begin1(data.cbegin(), data.cend(), pattern2);
	std::sregex_iterator end1;
	
	std::for_each(begin1, end1, [](const std::smatch& m)
		{
			std::cout << m[0] << std::endl;
		});
	system("pause");
	return EXIT_SUCCESS;
}