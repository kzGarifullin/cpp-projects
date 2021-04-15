//#define BOOST_DATE_TIME_NO_LIB
//
//#include <iostream>
//#include <string>
//#include <mutex>
//
//#include <boost/interprocess/allocators/allocator.hpp>
//#include <boost/interprocess/containers/string.hpp>
//#include <boost/interprocess/containers/vector.hpp>
//#include <boost/interprocess/managed_shared_memory.hpp>
//#include <boost/interprocess/sync/interprocess_mutex.hpp>
//#include <boost/interprocess/sync/interprocess_condition.hpp>
//
//int main(int argc, char** argv)
//{
//	system("pause");
//	const std::string n = "managed_shared_memory";
//
//	boost::interprocess::managed_shared_memory sm(
//		boost::interprocess::open_only, n.c_str());
//	using allocator_t_2 = boost::interprocess::allocator <char, boost::interprocess::managed_shared_memory::segment_manager>;
//	using string_t = boost::interprocess::basic_string <char, std::char_traits<char>, allocator_t_2>;
//	using allocator_t = boost::interprocess::allocator <string_t, boost::interprocess::managed_shared_memory::segment_manager>;
//	using vector_t = boost::interprocess::vector <string_t, allocator_t>;
//
//	allocator_t_2 a(sm.get_segment_manager());
//	allocator_t a2(sm.get_segment_manager());
//	auto v = sm.find <vector_t>("v").first;
//	//auto s = sm.find <string_t>("s").first;
//	auto m = sm.find <boost::interprocess::interprocess_mutex >("m").first;
//	auto c = sm.find <boost::interprocess::interprocess_condition >("c").first;
//	string_t s(a);
//	//vector_t v(a2);
//	string_t x = "exit";
//
//	do
//	{
//		std::unique_lock lock(*m);
//
//		c->wait(lock, [v]() {return !v->empty(); });
//
//		x = v->back();
//
//		std::cout << x;
//
//		v->pop_back();
//
//	} while (x !="exit");
//
//	system("pause");
//
//	return EXIT_SUCCESS;
//}













#define BOOST_DATE_TIME_NO_LIB

#include <string>
#include <mutex>

#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <iostream>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

int main()
{
	using namespace boost::interprocess;
	system("pause");
	const std::string n = "MySharedMemory";

	managed_shared_memory shm(open_only, n.c_str());
	std::cout << "shared memory opened\n";

	using CharAllocator = allocator<char, managed_shared_memory::segment_manager>;
	using MyShmString = basic_string<char, std::char_traits<char>, CharAllocator>;
	using StringAllocator = allocator<MyShmString, managed_shared_memory::segment_manager>;
	using MyShmStringVector = vector<MyShmString, StringAllocator>;

	CharAllocator    charallocator(shm.get_segment_manager());
	StringAllocator  stringallocator(shm.get_segment_manager());


	auto v = shm.find <MyShmStringVector>("myshmvector").first;

	auto m = shm.find <interprocess_mutex >("m").first;
	auto c = shm.find <interprocess_condition >("c").first;

	MyShmString mystring(charallocator);
	mystring = "exit";

	do
	{
		std::unique_lock lock(*m);

		c->wait(lock, [v]() {return !v->empty(); });

		mystring = v->back();

		std::cout << mystring << std::endl;

		v->pop_back();

	} while (mystring != "exit");

	system("pause");

	return EXIT_SUCCESS;
}