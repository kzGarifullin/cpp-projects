#include<iostream>
#include<fstream>
#include <string>

#include <sstream>

int main() {
	std::fstream fin("test.txt", std::ios::in);
	std::string s;
	std::getline(fin, s);
	int N = 0;
	std::cin >> N;
	//std::cout << s << std::endl;
	int a = (s.length()+2)*(N-1);	
	fin.seekp(a, std::ios::beg);
	std::string s2;
	std::getline(fin, s2);
	std::cout << s2 << std::endl;
}