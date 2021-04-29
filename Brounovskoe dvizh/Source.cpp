

#include <math.h>    
#include <chrono>
#include <ctime>
#include <cstdint>
#include <vector>
#include <random>
#include <cmath> 
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;

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
//		fruit.x = uid_x(dre);//новые случайныее коорд
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
//		for (std::size_t i = 0; i < N; ++i)//отрис спрайтй
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

struct Particle 
{
	float x; 
	float y; 
	float vx; 
	float vy; 
	float m;
};

int main(int argc, char** argv)
{
	std::vector < Particle > particles;
	const float dt = 0.01;
	const auto r = 4.0f;//radius of particle
	const auto R = 22.5f;//radius of broun particle
	int N = 100;//quantity of particles
	sf::RenderWindow window(sf::VideoMode(480U, 480U), "BROUN");
	for (int i = 0; i < N; i++) 
	{
		//Particle p0 = { rand()%480, rand() % 480, rand() % 100000 / 500.0 - 100, rand() % 100000 / 500.0 - 100, 4 };
		Particle p0 = { rand() % 480, rand() % 480, rand() % 200 - 100, rand() % 200 - 100, 4 };

		particles.push_back(p0);
		
	}
	
	Particle broun_part = { 480/2.0, 480/2.0, 0 , 0,40 };
	particles.push_back(broun_part);
	std::chrono::steady_clock::time_point time_point = std::chrono::steady_clock::now();//часы

	const std::chrono::microseconds delay(10000);// 50000 микросек врем€ шага когда таймер вырос да делэй делаетс€ шаг

	std::chrono::microseconds timer(0);
	while (window.isOpen())
	{
		timer += std::chrono::duration_cast <std::chrono::microseconds> (
						std::chrono::steady_clock::now() - time_point);//врем€ пред итерации добавили
			
		time_point = std::chrono::steady_clock::now();
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
		if (timer > delay)
		{
			timer = std::chrono::microseconds(0);
			//step(direction, snake, fruit, N, M);//делаем стэп
			for (int i = 0; i < N+1; i++) 
			{
				for (int j = 0; j < N+1; j++) 
				{
					if (i != j) 
					{
						//float d = pow(pow((particles[i].x - particles[j].x), 2) + pow((particles[i].y - particles[j].y), 2), 0.5);
						float d = sqrt((particles[i].x - particles[j].x)*(particles[i].x - particles[j].x) + (particles[i].y - particles[j].y)*(particles[i].y - particles[j].y));
						//std::cout << d<<" ";
						if (d < particles[i].m + particles[j].m) //радиус лиейно зависит от массы
						//if (d < 2*r)
						{
							float f = 50*(particles[i].m + particles[j].m - d);
							std::cout <<" dt ";
							particles[i].vx += f * (particles[i].x - particles[j].x) / d / particles[i].m * dt;
							particles[i].vy += f * (particles[i].y - particles[j].y) / d / particles[i].m * dt;
							particles[j].vx -= f * (particles[i].x - particles[j].x) / d / particles[j].m * dt;
							particles[j].vy -= f * (particles[i].y - particles[j].y) / d / particles[j].m * dt;

							//particles[i].vx = 0;
							//particles[i].vy = 0;
							//particles[j].vx = 0;
							//particles[j].vy = 0;
						//	std::cout << particles[i].vx << " || ";
						//	if(i==1)std::cout << particles[i].vx << " ||";
						//	std::cout << particles[i].vx << " ";
						}//силы отталкивани€
					}

				}
			}
			for (int i = 0; i < N+1; i++) 
			{
				//std::cout << "C";
				particles[i].x += particles[i].vx * dt;//new coordinates
				particles[i].y += particles[i].vy * dt;
				if (particles[i].x < 0)particles[i].x += 480;
				if (particles[i].y < 0)particles[i].y += 480;
				if (particles[i].x > 480)particles[i].x -= 480;
				if (particles[i].y > 480)particles[i].y -= 480;

			}
		}
		window.clear();

		for (auto i = 0; i < N+1; ++i)
		{
			if (particles[i].m > 10) {
				sf::CircleShape br_cir(40);

				br_cir.setPosition(particles[i].x-40, particles[i].y-40);
				std::cout << particles[i].x << " " << broun_part.y << " ";
				br_cir.setFillColor(sf::Color::White);
				window.draw(br_cir);
			}
			else {
				sf::CircleShape circle(4);

				circle.setPosition(particles[i].x, particles[i].y);
				circle.setFillColor(sf::Color::Blue);
				window.draw(circle);

			}
		
		}
		//std::cout << particles[15].vx << " ";
		/*sf::CircleShape br_cir(40);

		br_cir.setPosition(broun_part.x, broun_part.y);
		std::cout << broun_part.x<<" "<< broun_part.y<<" ";
		br_cir.setFillColor(sf::Color::White);
		window.draw(br_cir);*/
		window.display();
	}


}