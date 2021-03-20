#include <algorithm>
#include <iostream>
#include <regex>
#include <string>

int main(int argc, char** argv)
{
	std::string data = "1254 winner!@mail.ru reth!2ka.mi_tl@mail.ru dgh ta_ir465@yahoo.com ta_ir465@ ivanM@gmail.com q124 3434 masha_super_hero@phystech.edu  e77 2ka.mi_tl@mail.ru kukuha21,23@js.rer kukuha21,23@js!rer kivi@mail.ru ey jhjfjgf@mail.ru ";
	// kivi@mail.ru-менее 5 символов, поэтому не подходит    no
	//winner!@mail.ru- !   no
	//kukuha21,23@js!rer-! no
	//kukuha21,23@js.rer    yes
	//rules: [5:31] symbols, you can write A-Z and 1-9 and -_., 
	//std::regex pattern(R"([[:alnum:]][[:alnum:]|.|,|-|_]{4,31}@[[:alnum:]|.]+)");
	//std::regex pattern(R"([[:alnum:]][[:alnum:]|.|,|-|_]{4,31}@[[:alnum:]]+[.][[:alnum:]]+)");
	std::regex pattern(R"([[:alnum:]][[:alnum:]|.|,|-|_]{4,31}@([[:alnum:]]+[.][[:alnum:]]+)?)");
	//std::regex pattern(R"(\d{4})");
	std::sregex_iterator begin(data.cbegin(), data.cend(), pattern);
	std::sregex_iterator end;
	std::string s("this subject has a submarine as a subsequence");
	std::for_each(begin, end, [](const std::smatch& m)
		{
		
			if (m[1]!="") {
				for (std::size_t i = 0; i < m.size(); ++i)
				{
					std::cout << m[i] << " | ";
				}
				std::cout << std::endl;
			}
	

		});

	system("pause");

	return EXIT_SUCCESS;
}


