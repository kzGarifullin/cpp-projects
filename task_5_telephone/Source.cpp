#include <iostream>
#include <string>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
using namespace boost::multi_index;
struct Person
{
	std::string name;
	int phone;
	std::string data;
};

using Persons_multi_index = multi_index_container <
	Person, indexed_by <hashed_non_unique <member < Person, std::string, &Person::data > >,
	hashed_non_unique <
	member < Person, int, &Person::phone> >,
	random_access <> ,
	ordered_non_unique <
		member < Person, std::string, &Person::name > >> >;

int main(int argc, char** argv)
{
	Persons_multi_index Persons;

	Persons.insert({ "Kamil",    52334, "phoned today at 2pm" });
	Persons.insert({ "Maria",    14235, "phoned today at 1.5am" });
	Persons.insert({ "Alex",     78535, "phoned today at 7pm" });
	Persons.insert({ "Yana",    95789, "phoned today at 6am" });


	std::cout <<"phoned today at 2pm: " <<Persons.count("phoned today at 2pm")<<" person" << std::endl;

	auto& hashed_phone_index = Persons.get < 1 >();
	//std::cout << hashed_legs_index.count(14235) << std::endl;
	std::cout << hashed_phone_index.find(14235)->name << std::endl;//для обычного пользователя- поиск 
	//человека по номеру
	std::cout << std::endl;
	const auto & ordered_names_index = Persons.get < 3 > ();

	for (auto i:ordered_names_index)//для типографии- сортированный set
	{
		std::cout << i.name<< std::endl;
	}

	std::cout << std::endl;

	const auto& random_access_index = Persons.get < 2 >();

	std::cout << random_access_index[3].name << std::endl;//для рекламного агенства- доступ к 
	//произвольной записи

	
}