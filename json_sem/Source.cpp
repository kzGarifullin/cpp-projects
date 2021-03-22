#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include <locale>
#include <ostream>
#include <iostream>
#include <string>
#include "json.hpp"
using nlohmann::json;
class Adress
{
private:
	int m_num;
	std::string m_street;
public:
	Adress(int num = 7, std::string street = "Pushkin") : m_num(num), m_street(street)
	{
	}
	int get_m_num() { return m_num; }
	std::string get_m_street() { return m_street; }
	
	friend std::ostream& operator<< (std::ostream& out, const Adress& point);
	friend std::istream& operator>> (std::istream& in, Adress& point);
};

std::ostream& operator<< (std::ostream& out, const Adress& point)
{
	
	out << "Adress(" << point.m_num << ", " << point.m_street << ")";

	return out;
}

std::istream& operator>> (std::istream& in, Adress& point)
{
	in >> point.m_num;
	in >> point.m_street;
	return in;
}

class Point
{
private:
	double m_x, m_y;
	std::string m_z;
	Adress m_a;

public:
	Point(Adress a = {23,"Pushkin"}, double x = 0.0, double y = 0.0, std::string z = "kuku") : m_x(x), m_y(y), m_z(z), m_a(a)
	{
	}
	double get_m_x( )
	{
		return m_x;

	}
	double get_m_y(){ return m_y; }
	std::string get_m_z() { return m_z; }
	Adress get_m_a() { return m_a; }

	friend std::ostream& operator<< (std::ostream& out, const Point& point);
	friend std::istream& operator>> (std::istream& in, Point& point);
};

std::ostream& operator<< (std::ostream& out, const Point& point)
{
	out << "Point(" << point.m_x << ", " << point.m_y << ", " << point.m_z <<", "<< point.m_a<<")";
	return out;
}

std::istream& operator>> (std::istream& in, Point& point)
{
	
	in >> point.m_x;
	in >> point.m_y;
	in >> point.m_z;
	in >> point.m_a;
	return in;
}
void print(Point point,json&j) 
{
	j["m_x"] = point.get_m_x();
	j["m_y"] = point.get_m_y();
	j["m_z"] = point.get_m_z();
	j["Adress"]["num"] = point.get_m_a().get_m_num();
	j["Adress"]["street"] = point.get_m_a().get_m_street();

}
int main(int argc, char** argv)
{
	
	system("chcp 65001");
	auto path = std::filesystem::current_path();

	std::filesystem::create_directory(path / "directory_1");
	path = path / "directory_1";

	std::cout << "Enter a point: \n";

	Point point1;
	std::cin >> point1;

	Point point2;
	std::cin >> point2;

	Point point3;
	std::cin >> point3;

	Adress a{ 23,"Gogol" }; 
	std::cout << point1;


	json j;	
	std::filesystem::path path_output1 = path/"output1.txt";
	json j1;
	print(point1, j1);
	std::fstream fout(path_output1.string(), std::ios::out);

	fout << std::setw(4) << j1;

	std::filesystem::path path_output2 = path/"output2.txt";
	json j2;
	print(point2, j2);
	std::fstream fout2(path_output2.string(), std::ios::out);

	fout2 << std::setw(4) << j2;

	std::filesystem::path path_output3 = path/"output3.txt";
	json j3;
	print(point3, j3);
	std::fstream fout3(path_output3.string(), std::ios::out);

	fout3 << std::setw(4) << j3;
}