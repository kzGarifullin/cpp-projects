//#define BOOST_DATE_TIME_NO_LIB
//
//#include <iostream>
//#include <string>
//#include <mutex>
//
//#include <boost/interprocess/allocators/allocator.hpp>
//#include <boost/interprocess/containers/vector.hpp>
//#include <boost/interprocess/containers/string.hpp>
//#include <boost/interprocess/managed_shared_memory.hpp>
//#include <boost/interprocess/sync/interprocess_mutex.hpp>
//#include <boost/interprocess/sync/interprocess_condition.hpp>
//
//int main(int argc, char** argv)
//{
//	system("pause");
//
//
//
//
//	
//
//	using allocator_t_2 = boost::interprocess::allocator <char, boost::interprocess::managed_shared_memory::segment_manager>;
//	using string_t = boost::interprocess::basic_string <char, std::char_traits<char>, allocator_t_2>;
//	using allocator_t = boost::interprocess::allocator <string_t, boost::interprocess::managed_shared_memory::segment_manager>;
//	using vector_t = boost::interprocess::vector <string_t, allocator_t>;
//	const std::string n = "managed_shared_memory";
//	boost::interprocess::shared_memory_object::remove(n.c_str());
//	boost::interprocess::managed_shared_memory sm(
//		boost::interprocess::create_only, n.c_str(), 1024);
//	allocator_t_2 a(sm.get_segment_manager());
//	allocator_t a2(sm.get_segment_manager());
//	//auto v = sm.construct <vector_t>("v")(sm.get_segment_manager());
//
//	//auto s = sm.construct <string_t>("s")(sm.get_segment_manager());
//	string_t x(a);
//	x = "exit";
//	vector_t* v = sm.construct<vector_t>("v")(a2);
//	auto m = sm.construct <boost::interprocess::interprocess_mutex >("m")();
//	auto c = sm.construct <boost::interprocess::interprocess_condition >("c")();
//	
//	string_t x ="exit";
//
//	do 
//	{
//		std::cin >> x;
//
//		std::scoped_lock lock(*m);
//
//		v->push_back(x);
//
//		c->notify_one();
//
//	} while (x != "exit");
//
//	system("pause");
//
//	boost::interprocess::shared_memory_object::remove(n.c_str());
//
//
//	system("pause");
//
//	return EXIT_SUCCESS;
//}










#define BOOST_DATE_TIME_NO_LIB

#include <iostream>
#include <string>
#include <mutex>

#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/allocators/allocator.hpp>

#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>

int main()
{
    system("pause");
    using namespace boost::interprocess;
    //Typedefs
    using CharAllocator = allocator<char, managed_shared_memory::segment_manager>;
    using MyShmString = basic_string<char, std::char_traits<char>, CharAllocator>;
    using StringAllocator = allocator<MyShmString, managed_shared_memory::segment_manager>;
    using MyShmStringVector = vector<MyShmString, StringAllocator>;

    //Open shared memory
    //Remove shared memory on construction and destruction
    const std::string n = "MySharedMemory";
    shared_memory_object::remove(n.c_str());

    managed_shared_memory shm(create_only, n.c_str(), 10000);
    std::cout << "shared memory created\n";
    //Create allocators
    CharAllocator    charallocator(shm.get_segment_manager());
    StringAllocator  stringallocator(shm.get_segment_manager());

    MyShmString mystring(charallocator);
    mystring = "this is my text";

    MyShmStringVector* myshmvector = shm.construct<MyShmStringVector>("myshmvector")(stringallocator);

    auto m = shm.construct <interprocess_mutex >("m")();
    auto c = shm.construct <interprocess_condition >("c")();

    mystring = "exit";
    do
    {
        std::cin >> mystring;

        std::scoped_lock lock(*m);

        myshmvector->push_back(mystring);

        c->notify_all();

    } while (mystring != "exit");

    system("pause");

    shared_memory_object::remove(n.c_str());


    system("pause");
}





