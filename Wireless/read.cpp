#include <iostream>
#include <boost/asio.hpp>
std::atomic < bool > exit_flag;
std::string read_data(boost::asio::ip::tcp::socket& socket)
{
	const std::size_t length = 10;//server
	char buffer[length];
	boost::asio::read(socket, boost::asio::buffer(buffer, length));
	return std::string(buffer, length);
}

void read_data_until(std::string name,boost::asio::ip::tcp::socket& socket)
{
	while (true)
	{
		if (exit_flag)
		{
			break;
		}
		boost::asio::streambuf buffer;
		boost::asio::read_until(socket, buffer, '\n');
		std::string message;
		std::istream input_stream(&buffer);
		std::getline(input_stream, message, '\n');
		//return message;
		std::cout << name<<": "<< message << std::endl;
	}
}
void write_data(boost::asio::ip::tcp::socket& socket)
{
	//std::string data = "Hello, Network Programming!EOF";
	std::string data;
	
	        do
	        {
				getline(std::cin, data);
				boost::asio::write(socket, boost::asio::buffer(data+"\n"));
	        } while (data != "exit");
			exit_flag = true;

}
int main()
{
	system("chcp 1251");
	exit_flag = false;
	const std::size_t size = 30;
	
	auto port = 3333;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

	boost::asio::io_service io_service;

	try
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

		acceptor.bind(endpoint);

		acceptor.listen(size);

		boost::asio::ip::tcp::socket socket(io_service);

		acceptor.accept(socket);
		
		auto reader = std::thread(read_data_until, "Kamil", std::ref(socket));
		auto writer = std::thread(write_data, std::ref(socket));
		reader.join();
		writer.join();
		//std::cout << read_data_until(socket) << std::endl;
	}







	catch (boost::system::system_error& e)
	{
		std::cout << "Error occured! Error code = " << e.code() << ". Message: " << e.what() << std::endl;

		system("pause");

		return e.code().value();
	}

	system("pause");

	return EXIT_SUCCESS;
}





//
//
//
//
//
//
//
//
//class Chat
//{
//private:
//
//    using shared_memory_t = boost::interprocess::managed_shared_memory;
//    using manager_t = shared_memory_t::segment_manager;
//    using string_allocator_t = boost::interprocess::allocator<char, manager_t>;
//    using string_t = boost::interprocess::basic_string<char, std::char_traits<char>, string_allocator_t>;
//    using vector_allocator_t = boost::interprocess::allocator<string_t, manager_t>;
//    using vector_t = boost::interprocess::vector<string_t, vector_allocator_t>;
//    using mutex_t = boost::interprocess::interprocess_mutex;
//    using condition_t = boost::interprocess::interprocess_condition;
//    using counter_t = std::atomic < std::size_t >;
//
//public:
//
//    explicit Chat(const std::string& user_name) : m_user_name(user_name), m_exit_flag(false),
//        m_shared_memory(boost::interprocess::open_or_create, "sm", 10000)
//
//    {
//        m_vector = m_shared_memory.find_or_construct <vector_t>("v")(m_shared_memory.get_segment_manager());
//        m_mutex = m_shared_memory.find_or_construct <boost::interprocess::interprocess_mutex >("m")();
//        m_condition = m_shared_memory.find_or_construct <boost::interprocess::interprocess_condition >("c")();
//        m_users = m_shared_memory.find_or_construct <std::atomic < std::size_t >>("u")();
//        //m_messages  =  m_shared_memory.find_or_construct<std::atomic < std::size_t >>("mc")();
//
//        //...
//        (*m_users)++;
//        //...
//    }
//
//    ~Chat() noexcept = default;
//
//public:
//
//    void run()
//    {
//        auto reader = std::thread(&Chat::read, this);
//
//        write();
//
//        m_exit_flag = true;
//
//        m_condition->notify_all();
//
//        reader.join();
//
//        send_message(m_user_name + " left the chat");
//
//
//        if (!(--(*m_users)))
//        {
//            boost::interprocess::shared_memory_object::remove("sm");
//        }
//
//    }
//
//private:
//
//    void read()
//    {
//        show_history();
//
//        send_message(m_user_name + " joined the chat");
//
//
//        while (true)
//        {
//            std::unique_lock lock(*m_mutex);
//
//            m_condition->wait(lock, [this]() { return !m_vector->empty(); });
//            //m_condition->wait(lock, [this]() { return m_local_messages != m_messages; });
//
//            if (m_exit_flag)
//            {
//                break;
//            }
//            //if (m_local_messages!=*m_messages)
//
//            std::cout << m_vector->back();
//
//            m_vector->pop_back();
//            m_local_messages++;// mb ++
//
//        }
//    }
//
//    void show_history()
//    {
//        std::unique_lock lock(*m_mutex);
//
//        for (const auto& message : *m_vector)
//        {
//            std::cout << message << ' ';
//            std::cout << '\n';
//        }
//    }
//
//    void send_message(const std::string& message)
//    {
//        std::unique_lock lock(*m_mutex);
//        string_allocator_t   aloc_str(m_shared_memory.get_segment_manager());
//        string_t str(aloc_str);
//        str = "this is my text";
//        str = message.c_str();
//
//        m_vector->push_back(str);
//
//        m_condition->notify_all();
//
//        // m_messages--;
//        m_messages++;
//
//        // m_local_messages--;
//    }
//
//    void write()
//    {
//        /*string_allocator_t   aloc_str(m_shared_memory.get_segment_manager());
//        string_t str(aloc_str);
//        str = "this is my text";*/
//        std::string str;
//
//        do
//        {
//            std::cin >> str;
//            send_message(str);
//        } while (str != "exit");
//    }
//
//private:
//
//    static inline const std::string shared_memory_name = "shared_memory";
//
//private:
//
//    std::string m_user_name;
//
//    std::atomic < bool > m_exit_flag;
//
//    shared_memory_t m_shared_memory;
//
//    vector_t* m_vector;
//    mutex_t* m_mutex;
//    condition_t* m_condition = 0;
//    counter_t* m_users = 0;
//    //counter_t* m_messages=0;
//
//    std::size_t m_local_messages = 0;
//    std::size_t m_messages = 0;
//};
//
//int main(int argc, char** argv)
//{
//    boost::interprocess::shared_memory_object::remove("sm");
//    std::string user_name;
//
//    std::cout << "Enter your name: ";
//
//    std::getline(std::cin, user_name);
//
//    Chat(user_name).run();
//
//    system("pause");
//
//    return EXIT_SUCCESS;
//}