#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#ifndef _HAS_AUTO_PTR_ETC
#define _HAS_AUTO_PTR_ETC 1
#endif
#include <unordered_map>
#include <bitset>
#include <chrono>
#include <codecvt>
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <fstream>
#include <iostream>
#include <iterator>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>
#include <boost/locale.hpp>
#include <Windows.h>
std::string convert_locale_to_utf(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::to_utf < char >(string, locale);
}

std::string convert_utf_to_locale(const std::string& string)
{
	boost::locale::generator generator;
	generator.locale_cache_enabled(true);

	std::locale locale =
		generator(boost::locale::util::get_system_locale());

	return boost::locale::conv::from_utf < char >(string, locale);
}

std::wstring convert_utf8_to_wstring(const std::string& string)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
	return converter.from_bytes(string);
}

std::string convert_wstring_to_utf8(const std::wstring& wstring)
{
	std::wstring_convert < std::codecvt_utf8 < wchar_t > > converter;
	return converter.to_bytes(wstring);
}

std::wstring convert_string_to_wstring(
	const std::string& string,
	const std::locale& locale = std::locale())
{
	std::vector < wchar_t > buffer(string.size());

	std::use_facet < std::ctype < wchar_t > >(locale).widen(
		string.data(),
		string.data() + string.size(),
		buffer.data());

	return std::wstring(buffer.data(), buffer.size());
}

std::string convert_wstring_to_string(
	const std::wstring& wstring,
	const std::locale& locale = std::locale())
{
	std::vector < char > buffer(wstring.size());

	std::use_facet < std::ctype < wchar_t > >(locale).narrow(
		wstring.data(),
		wstring.data() + wstring.size(),
		'?', buffer.data()); // default character

	return std::string(buffer.data(), buffer.size());
}
int main(int argc, char** argv)
{
		system("chcp 1251"); 
		std::string string;
		std::cin >> string;
		std::string u8string = convert_locale_to_utf(string);
		SetConsoleCP      (65001);
		SetConsoleOutputCP(65001);
		std::u32string u32string = 
			boost::locale::conv::utf_to_utf < char32_t, char > (u8string);
		/*for (auto c : u32string)
		{
			std::cout << c << '_';
		}*/
		//string = convert_utf_to_locale(string);
		std::string string_new;
		system("chcp 1251");
		//std::cout << string << ' ' << string.length() << std::endl;
	    std::unordered_map<int, std::string> u = {
	  {1072,"a"},
	  {1073,"b"},
	  {1074,"v"},
	  {1075,"g"},
	  {1076,"d"},
	  {1077,"e"},
	  {1078,"zh"},
	  {1079,"z"},
	  {1080,"i"},
	  {1081,"y"},
	  {1082,"k"},
	  {1083,"l"},
	  {1084,"m"},
	  {1085,"n"},
	{1086,"o"},
	  {1087,"p"},
	  {1088,"r"},
	  {1089,"s"},
	{1090,"t"},
	  {1091,"u"},
	  {1092,"f"},
	  {1093,"h"},
		{1094,"c"},
	  {1095,"ch"},
	  {1096,"sh"},
	  {1097,"ssh"},
		{1098,"y"},
		{1099,"i"},
		{1100,"y"},
		{1101,"a"},
		{1102,"yu"},
		{1103,"ya"},
	};
	for (auto c : u32string)
	{
		string_new += u[c];
	}
	string_new = convert_utf_to_locale(string_new);

	std::cout << string_new;
	return EXIT_SUCCESS;
}