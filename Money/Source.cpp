#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <locale>
#include <sstream>
#include <Windows.h> 
void show_currency_symbol(const std::string& locale_name)
{
	std::cout << locale_name << " : " <<
		std::use_facet < std::moneypunct < char, false > >(
			std::locale(locale_name)).curr_symbol() << std::endl;
}
int main(int argc, char** argv)
{
	SetConsoleCP(CP_UTF8); // настраиваем консоль, чтобы она могла корректно
	SetConsoleOutputCP(CP_UTF8); // работать с выводом символов в кодировке UTF-8
	std::istringstream in("$1,234.56 2.22 USD  3.33");
	long double v1, v2;
	std::string v3;
	in.imbue(std::locale("en_US.UTF-8"));
	in >> std::get_money(v1) >> std::get_money(v2) >> std::get_money(v3, true);
	std::cout.imbue(std::locale("en_US.UTF-8"));
	std::cout << std::showbase
		<< "en_US: " << std::put_money(v1)<< '\n';
	std::cout << std::showbase
		<< "en_US: " << std::put_money(v1)
		<< " or " << std::put_money(v1, true) << '\n';
	std::cout.imbue(std::locale("ru_RU.UTF-8"));
	std::cout << "ru_RU: " << std::put_money(v1*74.5)
		<< " or " << std::put_money(v1*74.5, true) << '\n';
}