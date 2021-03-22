#include<iostream>
#include<fstream>
#include <string>
#include <iterator>
#include <sstream>

int main()
{
	std::fstream fin("test.txt", std::ios::in);
	std::ofstream out;          // поток для записи
	std::string final;
	std::string s;
	bool flag_zv = false;
	while (std::getline(fin, s)) {
		//std::cout << s <<std::endl; // выводим на экран
		bool flag = false;
		bool flag_spec = false;
		bool flag_kov = false;

		bool del = false;
		for (int i = 0; i < s.length(); i++)
		{

			if (s[i] == '\"')
			{
				std::cout << s[i];
				final += s[i];

				if (flag_kov == true)
				{

					if (flag_spec == true)
					{
						flag_kov = true;
						flag_spec = false;
					}
					else flag_kov = false;

				}
				else flag_kov = true;
			}
			else {
				if (flag_kov == true) //если в ковычках-все выводим
				{
					std::cout << s[i];
					final += s[i];
					if (s[i] == '\\') {
						flag_spec = true;
					}
				}
				else
				{
					if (s[i] == '\*')
					{
						if (flag_zv == true) { flag_zv = false; flag = false; }
						else { flag_zv = true; }
					}
					else
					{
						if (s[i] == '/')
						{

							if (flag == true) { break; }
							flag = true;
						}
						else
						{
							if (flag_zv == true) {}
							else {
								std::cout << s[i];
								final += s[i];
								flag = false;
							}
						}
					}

				}
			}


		}
		std::cout << std::endl;
		final += '\n';
	}
	std::cout << final;
	std::fstream fout;
	fout.open("test.txt",std::ios::out);
	
	fout.seekg(0, std::ios::beg);
	fout << final;

}
