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

void step(Direction direction, Player &player, const int N, const int M)
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
int main()
{
    const int N = 600;
    const int M = 480;
    int speed = 4;

    bool field[N][M] = { false };
    srand(time(0));
    RenderWindow window(VideoMode(N, M), "The Tron Game!");
    
    window.setFramerateLimit(60);

    Texture texture;
    texture.loadFromFile("background.jpg");
    Sprite sBackground(texture);

    Player p1 = { 1, 1, Color::Red };
    Player p2 = { 10,10,Color::Green };

    Sprite sprite;
    RenderTexture t;
    t.create(N, M);
    t.setSmooth(true);
    sprite.setTexture(t.getTexture());
    t.clear();  t.draw(sBackground);
    Direction direction1 = Direction::right;
    Direction direction2 = Direction::left;
    bool Game = true;

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Left)) if (direction1 != Direction::right) direction1 = Direction::left;
        if (Keyboard::isKeyPressed(Keyboard::Right)) if (direction1 != Direction::left)  direction1 = Direction::right;
        if (Keyboard::isKeyPressed(Keyboard::Up)) if (direction1 != Direction::down) direction1 = Direction::up;
        if (Keyboard::isKeyPressed(Keyboard::Down)) if (direction1 != Direction::up) direction1 = Direction::down;
        if (Keyboard::isKeyPressed(Keyboard::A)) if (direction2 != Direction::right) direction2 = Direction::left;
        if (Keyboard::isKeyPressed(Keyboard::D)) if (direction2 != Direction::left)  direction2 = Direction::right;
        if (Keyboard::isKeyPressed(Keyboard::W))  if (direction2 != Direction::down) direction2 = Direction::up;
        if (Keyboard::isKeyPressed(Keyboard::S)) if (direction2 != Direction::up) direction2 = Direction::down;

        if (!Game)    continue;

        for (int i = 0; i < speed; i++)
        {
            step(direction1, p1, N, M); step(direction2, p2, N, M);
            if (field[p1.x][p1.y] == 1) Game = false;
            if (field[p2.x][p2.y] == 1) Game = false;
            field[p1.x][p1.y] = 1;
            field[p2.x][p2.y] = 1;

            CircleShape c(3);
            c.setPosition(p1.x, p1.y); c.setFillColor(p1.color);    t.draw(c);
            c.setPosition(p2.x, p2.y); c.setFillColor(p2.color);    t.draw(c);
            t.display();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}


//
//#include <chrono>
//#include <ctime>
//#include <cstdint>
//#include <vector>
//#include <random>
//
//#include <SFML/Graphics.hpp>
//
//using namespace sf;
//
//enum class Direction
//{
//	down,
//	left,
//	right,
//	up
//};
//
//struct Snake
//{
//	int x;
//	int y;
//};
//
//struct Fruit
//{
//	int x;
//	int y;
//};
//
//void step(Direction direction, std::vector < Snake >& snake, Fruit& fruit, const int N, const int M)
//{
//	static std::default_random_engine dre;
//	static std::uniform_int_distribution <> uid_x(0, N - 1);
//	static std::uniform_int_distribution <> uid_y(0, M - 1);
//
//	for (std::size_t i = snake.size() - 1; i > 0; --i)
//	{
//		snake[i].x = snake[i - 1].x;
//		snake[i].y = snake[i - 1].y;
//	}
//
//	if (direction == Direction::down)  snake[0].y++;
//	if (direction == Direction::left)  snake[0].x--;
//	if (direction == Direction::right) snake[0].x++;
//	if (direction == Direction::up)    snake[0].y--;
//
//	if ((snake[0].x == fruit.x) && (snake[0].y == fruit.y))
//	{
//		snake.push_back(snake.back());//в змейку добавили узел
//
//		fruit.x = uid_x(dre);//новые случайные коорд
//		fruit.y = uid_y(dre);
//	}//поедание фрукта
//
//	if (snake[0].x <= -1) snake[0].x = N - 1;//переброс змейки за аут
//	if (snake[0].x >= N) snake[0].x = 0;
//	if (snake[0].y <= -1) snake[0].y = M - 1;
//	if (snake[0].y >= M) snake[0].y = 0;
//
//	//for (std::size_t i = 1; snake.size() > 2 && i < snake.size(); ++i)// съела саму себ€
//	//{
//	//	if (snake[0].x == snake[i].x && snake[0].y == snake[i].y)
//	//	{
//	//		snake.erase(snake.begin() + i, snake.end());
//	//		break;
//	//	}
//	//}
//}
//
//int main(int argc, char** argv)
//{
//	const int N = 30;
//	const int M = 20;
//
//	const std::size_t size = 16;
//
//	RenderWindow application(VideoMode(size * N, size * M), "SNAKE");
//
//	Texture texture_1, texture_2, texture_3;
//
//	texture_1.loadFromFile("images/white.png");
//	texture_2.loadFromFile("images/red.png");
//	texture_3.loadFromFile("images/green.png");
//
//	Sprite sprite_1(texture_1);
//	Sprite sprite_2(texture_2);
//	Sprite sprite_3(texture_3);//sprite дл€ текстуры
//
//	Direction direction = Direction::right;//нач движ слева на право
//
//	std::vector < Snake > snake = { {0, 0}, { 1, 0 }, { 2, 0 }, { 3, 0 } };//экземпл€р змеи
//
//	Fruit fruit = { 10, 10 };//фрукт ебать
//
//	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();//часы
//
//	const std::chrono::microseconds delay(50000);// 50000 микросек врем€ шага когда таймер вырос да делэй делаетс€ шаг
//
//	std::chrono::microseconds timer(0);
//
//	while (application.isOpen())
//	{
//		timer += std::chrono::duration_cast <std::chrono::microseconds> (
//			std::chrono::steady_clock::now() - time_point);//врем€ пред итерации добавили
//
//		time_point = std::chrono::steady_clock::now();
//
//		Event event;// закрытие окна один ивент
//
//		while (application.pollEvent(event))
//		{
//			if (event.type == Event::Closed)
//			{
//				application.close();
//			}
//		}
//
//		if (Keyboard::isKeyPressed(Keyboard::Left))  direction = Direction::left;
//		if (Keyboard::isKeyPressed(Keyboard::Right)) direction = Direction::right;//елси нажата кнопка то мы соответ образом измен напрвлени€
//		if (Keyboard::isKeyPressed(Keyboard::Up))    direction = Direction::up;
//		if (Keyboard::isKeyPressed(Keyboard::Down))  direction = Direction::down;
//
//		if (timer > delay)
//		{
//			timer = std::chrono::microseconds(0);
//			step(direction, snake, fruit, N, M);//делаем стэп
//		}
//
//		application.clear(Color::White);//1 шаг отрисовки
//
//		for (std::size_t i = 0; i < N; ++i)//отрис спрайт
//		{
//			for (std::size_t j = 0; j < M; ++j)
//			{
//				sprite_1.setPosition(
//					static_cast <float> (i * size),
//					static_cast <float> (j * size));
//
//				application.draw(sprite_1);
//			}
//		}
//
//		for (const auto& part : snake)//отрисовываем змею
//		{
//			sprite_2.setPosition(
//				static_cast <float> (part.x * size),
//				static_cast <float> (part.y * size));
//
//			application.draw(sprite_2);
//		}
//
//		{
//			sprite_3.setPosition(
//				static_cast <float> (fruit.x * size),
//				static_cast <float> (fruit.y * size));
//
//			application.draw(sprite_3);
//		}
//
//		application.display();
//	}
//
//	system("pause");
//
//	return EXIT_SUCCESS;
//}
//
//
//
