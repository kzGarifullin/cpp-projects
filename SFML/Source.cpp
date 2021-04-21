//#include <array>
//#include <ctime>
//#include <cstdint>
//#include <random>
//
//#include <SFML/Graphics.hpp>
//
//using namespace sf;
//
//enum class Box
//{
//	empty,
//	one,
//	two,
//	three,
//	four,
//	five,
//	six,
//	seven,
//	eight,
//	bomb,
//	closed,
//	flag
//};
//
//int main(int argc, char** argv)
//{
//	std::default_random_engine dre;
//	std::uniform_int_distribution <> uid(0, 4);//раскидывать бомбы по полю
//
//	const std::size_t box_size = 32;//размер клетки
//	const std::size_t field_size = 10;//10 на 10
//
//	Box grid_back[field_size + 2][field_size + 2];//бэк энд
//	Box grid_view[field_size + 2][field_size + 2];// фронт энд что отображаетс€
//
//	for (std::size_t i = 1; i <= field_size; ++i)
//	{
//		for (std::size_t j = 1; j <= field_size; ++j)
//		{
//			grid_view[i][j] = Box::closed;
//
//			if (uid(dre) == 0)
//			{
//				grid_back[i][j] = Box::bomb;//20 процетов что бомб
//			}
//			else
//			{
//				grid_back[i][j] = Box::empty;
//			}
//		}
//	}
//
//	std::size_t counter = 0;
//
//	for (std::size_t i = 1; i <= field_size; ++i)
//	{
//		for (std::size_t j = 1; j <= field_size; ++j)
//		{
//			counter = 0;
//
//			if (grid_back[i][j] == Box::bomb) continue;//если бомба
//
//			if (grid_back[i + 1][j + 0] == Box::bomb) ++counter;
//			if (grid_back[i + 0][j + 1] == Box::bomb) ++counter;
//			if (grid_back[i - 1][j - 0] == Box::bomb) ++counter;
//			if (grid_back[i - 0][j - 1] == Box::bomb) ++counter;
//			if (grid_back[i + 1][j + 1] == Box::bomb) ++counter;
//			if (grid_back[i - 1][j - 1] == Box::bomb) ++counter;
//			if (grid_back[i - 1][j + 1] == Box::bomb) ++counter;
//			if (grid_back[i + 1][j - 1] == Box::bomb) ++counter;
//
//			grid_back[i][j] = static_cast <Box> (counter);
//		}
//	}
//
//	RenderWindow application(VideoMode(384, 384), "MINESWEEPER");//создаетс€ окно размером 384 видномод-допускаетс€ дин визуализаци€
//
//	Texture texture;
//
//	texture.loadFromFile("images/tiles.jpg");
//
//	Sprite sprite(texture);//кусочек структуры
//
//	Vector2i position;//вектор из двух чисел флоат математический позиц€ курсора 
//
//	std::size_t box_number_x = 0;
//	std::size_t box_number_y = 0;
//
//	auto updated = false;
//
//	Event event;//событие
//
//	while (application.isOpen())//бесконечно пока не нажмут крестик 
//	{
//		position = Mouse::getPosition(application);//запрашиваем позицию мышки
//
//		box_number_x = position.x / box_size;//вычисл€ем над которыми находитс€ наш курсор
//		box_number_y = position.y / box_size;
//
//		updated = false;
//
//		while (application.pollEvent(event))//внутр цикл   событийно ... прогр
//		{
//			if (event.type == Event::Closed)//событие было зарегистр попадает в очередь событий
//				//извлекаем из очереди обрабатываем
//			{
//				application.close();//закртыо окно   такое событие обрабатываем
//			}
//
//			if (event.type == Event::MouseButtonPressed)// нажата кнопка мыши
//			{
//				if (1 <= box_number_x && box_number_x <= field_size &&
//					1 <= box_number_y && box_number_y <= field_size)
//				{
//					if (event.key.code == Mouse::Left)//лева€ или права€
//					{
//						grid_view[box_number_x][box_number_y] = grid_back[box_number_x][box_number_y];// флаг
//					}
//					else if (event.key.code == Mouse::Right)//лева€
//					{
//						grid_view[box_number_x][box_number_y] = Box::flag;//открывем клетку переносим из бэка на фронт
//					}
//
//					updated = true;
//				}
//			}
//		}
//
//		application.clear(Color::White);//отрисовка стираем все что было в окне на данный момент
//		//дро - рэндеринг
//		//дисплэй
//		for (std::size_t i = 1; i <= field_size; ++i)
//		{
//			for (std::size_t j = 1; j <= field_size; ++j)//цикл по всем клеткам
//			{
//				if (updated && grid_view[box_number_x][box_number_y] == Box::bomb)// если нажади на клетку и там бомба
//				{
//					grid_view[i][j] = grid_back[i][j];//проиграли показываем все поле
//				}
//
//				sprite.setTextureRect(IntRect(
//					static_cast <int> (grid_view[i][j]) * box_size, 0, box_size, box_size));//вырезаем нужный квадрат из текстуры
//
//				sprite.setPosition(//в какой точке отрисовывать квадратик
//					static_cast <float> (i * box_size),
//					static_cast <float> (j * box_size));//каст чтобы избавитьс€ от предупреждений компил€тора
//
//				application.draw(sprite);// нарисовали все спрайты в цикле
//			}
//		}
//
//		application.display();//
//	}
//
//	system("pause");
//
//	return EXIT_SUCCESS;
//}


//
//
//
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







#include <array>
#include <ctime>
#include <cstdint>
#include <random>

#include <algorithm>

#include <SFML/Graphics.hpp>

using namespace sf;
int main() {
	RenderWindow application(VideoMode(520, 450), "ARCANOID");
	Texture t1, t2, t3, t4;
	t1.loadFromFile("images/block.jpg");
	t2.loadFromFile("images/backround.jpg");
	t3.loadFromFile("images/ball.jpg");
	t4.loadFromFile("images/paddle.jpg");
	Sprite backround(t2);
	Sprite ball(t3);
	Sprite paddle(t4);
	paddle.setPosition(1.0f, 440.0f);
	const std::size_t size = 10;
	
	std::vector<Sprite> blocks:
	for (auto i = 1; i <= size; i++) 
	{
		for (auto j = 1; j <= size; j++)
		{
			blocks.push_back(Sprite());
			blocks.back().setTexture(t1);
			blocks.back().setPosition(i*42.0f,j* 20.0f);
		}
	
	}

	float x = 300.0f;
	float y = 300.0f;
	float dx = 0.25f;
	float dy = 0.25f;
	std::default_random_engine dre;

	std::uniform_real_distribution<float> urd(0.25f,0.50f);
	Event event;
	while (application.isOpen())
	{
		while (application.pollEvent(event)) 
		{
			if (event.type == Event::Closed) 
			{
				application.close();
			}
		
		
		
		}
		x += dx;
		block.erase(std::remove_if(std::begin(blocks), std::end(blocks)[x, y, &dx](const auto& sprite)
			{if (FloatRect(x+3.0f,y+3.0f,6.0f,6.0f).intersects(sprite.getGlobalBounds())) 
		{ 
			dx = -dx;
			return true; 
		}
		return false; 
			}),
			std::end(blocks));
	


	block.erase(std::remove_if(std::begin(blocks), std::end(blocks)[x, y, &dx](const auto& sprite)
		{if (FloatRect(x + 3.0f, y + 3.0f, 6.0f, 6.0f).intersects(sprite.getGlobalBounds()))
		{
		dy = -dy;
		return true;
		}
		return false;
		}),
		std::end(blocks));

	if (x < 0.0f || x>520.0f - 12.0f) dx = -dx;
	if (y < 0.0f || y>450.0f - 12.0f) dy = -dy;
	if (Keyboard::isKeyPressed(keybord::Right))
	{
		if (paddle.getGlobalBounds().left + paddle.getGlobalBounds().width < 519.0f)
		{
			paddle.move(-0.5f, 0.0f);
		}
	}
	if (FloatRect(x, y, 12.0f, 12.0f).intersects(paddle.getGlobalBounds()))
	{
		dy = -urd(dre);
	}
	ball.setPossition(x, y);
	application.clear();
	apllication.draw(background);
	apllication.draw(ball);
	apllication.draw(paddle);
	for (const auto& sprite : blocks)
	{
		application.draw(sprite);
	}
	apllication.display();
	}



}