#include <iostream>

#include <boost/asio.hpp>
//client
std::atomic < bool > exit_flag_w=false;
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
		
		boost::asio::streambuf buffer;

		boost::asio::read_until(socket, buffer, '\n');

		std::string message;

		std::istream input_stream(&buffer);
		std::getline(input_stream, message, '\n');

		//return message;
		if (message == "exit")
		{
			break;
		}
		std::cout << name << ": " << message << std::endl;
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
	exit_flag_w = true;

}

int main(int argc, char** argv)
{
	system("chcp 1251");
	exit_flag_w = false;
	std::string raw_ip_address = "127.0.0.1";

	auto port = 3333;

	try
	{
		boost::asio::ip::tcp::endpoint endpoint(
			boost::asio::ip::address::from_string(raw_ip_address), port);

		boost::asio::io_service io_service;

		boost::asio::ip::tcp::socket socket(io_service, endpoint.protocol());

		socket.connect(endpoint);
		
		auto reader = std::thread(read_data_until,"Ann", std::ref(socket));
		auto writer = std::thread(write_data, std::ref(socket));
		writer.join();
		reader.join();
		
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

