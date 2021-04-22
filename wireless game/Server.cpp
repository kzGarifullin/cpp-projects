#include <iostream>
#include <boost/asio.hpp>

#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;
enum class Direction
{
	down,
	left,
	right,
	up
};



struct Player
{
	int x, y;
	Color color;
};

void step(Direction direction, Player& player, const int N, const int M)
{
	if (direction == Direction::down)  player.y++;
	if (direction == Direction::left)  player.x--;
	if (direction == Direction::right) player.x++;
	if (direction == Direction::up)    player.y--;
	if (player.x < 0) player.x = N - 1;
	if (player.x >= N) player.x = 0;
	if (player.y < 0) player.y = M - 1;
	if (player.y >= M) player.y = 0;
}
std::atomic < bool > exit_flag = false;
std::string read_data(boost::asio::ip::tcp::socket& socket)
{
	const std::size_t length = 10;//server
	char buffer[length];
	boost::asio::read(socket, boost::asio::buffer(buffer, length));
	return std::string(buffer, length);
}

void read_data_until(std::string name, boost::asio::ip::tcp::socket& socket)
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
		boost::asio::write(socket, boost::asio::buffer(data + "\n"));
	} while (data != "exit");
	exit_flag = true;

}
void give(boost::asio::ip::tcp::socket& socket, std::string data)
{
	//std::string data = "Hello, Network Programming!EOF";

	boost::asio::write(socket, boost::asio::buffer(data));
}
std::string get(boost::asio::ip::tcp::socket& socket)
{

	boost::asio::streambuf buffer;
	boost::asio::read_until(socket, buffer, '!');
	std::string message;
	std::istream input_stream(&buffer);
	std::getline(input_stream, message, '!');
	return message;

}
int main()
{
	system("chcp 1251");
	//exit_flag = false;
	const std::size_t size = 30;

	auto port = 8000;

	boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address_v4::any(), port);

	boost::asio::io_service io_service;

	try
	{
		boost::asio::ip::tcp::acceptor acceptor(io_service, endpoint.protocol());

		acceptor.bind(endpoint);

		acceptor.listen(size);

		boost::asio::ip::tcp::socket socket(io_service);

		acceptor.accept(socket);

		/*auto reader = std::thread(read_data_until, "Kamil", std::ref(socket));
		auto writer = std::thread(write_data, std::ref(socket));
		reader.join();
		writer.join();*/
		//std::cout << read_data_until(socket) << std::endl;

		const int N = 600;
		const int M = 480;
		int speed = 2;

		bool field[N][M] = { false };
		srand(time(0));
		RenderWindow window2(VideoMode(N, M), "The Tron Game!");

		window2.setFramerateLimit(60);

		Texture texture;
		texture.loadFromFile("background.jpg");
		Sprite sBackground(texture);
		Player p2 = { 300, M*0.95, Color::Red };
		Player p1 = { 300,M*0.05,Color::Green };
		Sprite sprite;
		RenderTexture t;
		t.create(N, M);
		t.setSmooth(true);
		sprite.setTexture(t.getTexture());
		t.clear();  t.draw(sBackground);
		Direction direction2 = Direction::down;
		Direction direction1 = Direction::up;
		bool Game = true;
		bool cl=false;
		while (window2.isOpen())
		{
			Event e;
			while (window2.pollEvent(e))
			{
				if (e.type == Event::Closed)
					cl = true;
			}
			if (cl == true) { window2.close(); give(socket, "HT!"); }
			if (Keyboard::isKeyPressed(Keyboard::A)) if (direction1 != Direction::right)
			{
				direction1 = Direction::left;
				//give(socket, "LT!");
			}
			if (Keyboard::isKeyPressed(Keyboard::D)) if (direction1 != Direction::left)
			{
				direction1 = Direction::right;
				//give(socket, "RT!");
			}
			if (Keyboard::isKeyPressed(Keyboard::W)) if (direction1 != Direction::down)
			{
				direction1 = Direction::up;
				//give(socket, "UT!");
			}
			if (Keyboard::isKeyPressed(Keyboard::S)) if (direction1 != Direction::up)
			{
				direction1 = Direction::down;
				//give(socket, "DT!");
			}
			if (cl) 
			{
				if (direction1 == Direction::down)give(socket, "DT!");
				if (direction1 == Direction::up)give(socket, "UT!");
				if (direction1 == Direction::left)give(socket, "LT!");
				if (direction1 == Direction::right)give(socket, "RT!");
			}
			else
			{
				if (direction1 == Direction::down)give(socket, "DF!");
				if (direction1 == Direction::up)give(socket, "UF!");
				if (direction1 == Direction::left)give(socket, "LF!");
				if (direction1 == Direction::right)give(socket, "RF!");
			
			}
			auto pl_data = get(socket);
			if (pl_data[1] == 'T') cl=true;
			if (pl_data[1] == 'F') cl = false;
			if (pl_data[0] == 'L') direction2 = Direction::right;
			if (pl_data[0] == 'R') direction2 = Direction::left;
			if (pl_data[0] == 'U') direction2 = Direction::down;
			if (pl_data[0] == 'D') direction2 = Direction::up;
			/*
			if (Keyboard::isKeyPressed(Keyboard::A)) if (direction2 != Direction::right) direction2 = Direction::left;
			if (Keyboard::isKeyPressed(Keyboard::D)) if (direction2 != Direction::left)  direction2 = Direction::right;
			if (Keyboard::isKeyPressed(Keyboard::W))  if (direction2 != Direction::down) direction2 = Direction::up;
			if (Keyboard::isKeyPressed(Keyboard::S)) if (direction2 != Direction::up) direction2 = Direction::down;
	        */
			if (!Game)    continue;

			for (int i = 0; i < speed; i++)
			{
				step(direction1, p2, N, M); step(direction2, p1, N, M);
				if (field[p2.x][p2.y] == 1) Game = false;
				if (field[p1.x][p1.y] == 1) Game = false;
				field[p2.x][p2.y] = 1;
				field[p1.x][p1.y] = 1;

				CircleShape c(3);
				c.setPosition(p2.x, p2.y); c.setFillColor(p2.color);    t.draw(c);
				c.setPosition(p1.x, p1.y); c.setFillColor(p1.color);    t.draw(c);
				t.display();
			}
			window2.clear();
			window2.draw(sprite);
			window2.display();
		}




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
//#include <SFML/Graphics.hpp>
//#include <time.h>
//using namespace sf;
//enum class Direction
//{
//	down,
//	left,
//	right,
//	up
//};
//
//
//
//struct Player
//{
//	int x, y;
//	Color color;
//};
//
//void step(Direction direction, Player& player, const int N, const int M)
//{
//	if (direction == Direction::down)  player.y++;
//	if (direction == Direction::left)  player.x--;
//	if (direction == Direction::right) player.x++;
//	if (direction == Direction::up)    player.y--;
//	if (player.x < 0) player.x = N - 1;
//	if (player.x >= N) player.x = 0;
//	if (player.y < 0) player.y = M - 1;
//	if (player.y >= M) player.y = 0;
//}
//int main()
//{
//	const int N = 600;
//	const int M = 480;
//	int speed = 4;
//
//	bool field[N][M] = { false };
//	srand(time(0));
//	RenderWindow window(VideoMode(N, M), "The Tron Game!");
//
//	window.setFramerateLimit(60);
//
//	Texture texture;
//	texture.loadFromFile("background.jpg");
//	Sprite sBackground(texture);
//
//	Player p1 = { 1, 1, Color::Red };
//	Player p2 = { 10,10,Color::Green };
//
//	Sprite sprite;
//	RenderTexture t;
//	t.create(N, M);
//	t.setSmooth(true);
//	sprite.setTexture(t.getTexture());
//	t.clear();  t.draw(sBackground);
//	Direction direction1 = Direction::right;
//	Direction direction2 = Direction::left;
//	bool Game = true;
//
//	while (window.isOpen())
//	{
//		Event e;
//		while (window.pollEvent(e))
//		{
//			if (e.type == Event::Closed)
//				window.close();
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::Left)) if (direction1 != Direction::right) direction1 = Direction::left;
//		if (Keyboard::isKeyPressed(Keyboard::Right)) if (direction1 != Direction::left)  direction1 = Direction::right;
//		if (Keyboard::isKeyPressed(Keyboard::Up)) if (direction1 != Direction::down) direction1 = Direction::up;
//		if (Keyboard::isKeyPressed(Keyboard::Down)) if (direction1 != Direction::up) direction1 = Direction::down;
//		if (Keyboard::isKeyPressed(Keyboard::A)) if (direction2 != Direction::right) direction2 = Direction::left;
//		if (Keyboard::isKeyPressed(Keyboard::D)) if (direction2 != Direction::left)  direction2 = Direction::right;
//		if (Keyboard::isKeyPressed(Keyboard::W))  if (direction2 != Direction::down) direction2 = Direction::up;
//		if (Keyboard::isKeyPressed(Keyboard::S)) if (direction2 != Direction::up) direction2 = Direction::down;
//
//		if (!Game)    continue;
//
//		for (int i = 0; i < speed; i++)
//		{
//			step(direction1, p1, N, M); step(direction2, p2, N, M);
//			if (field[p1.x][p1.y] == 1) Game = false;
//			if (field[p2.x][p2.y] == 1) Game = false;
//			field[p1.x][p1.y] = 1;
//			field[p2.x][p2.y] = 1;
//
//			CircleShape c(3);
//			c.setPosition(p1.x, p1.y); c.setFillColor(p1.color);    t.draw(c);
//			c.setPosition(p2.x, p2.y); c.setFillColor(p2.color);    t.draw(c);
//			t.display();
//		}
//
//		window.clear();
//		window.draw(sprite);
//		window.display();
//	}
//
//	return 0;
//}