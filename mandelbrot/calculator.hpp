#pragma once
//расчет множеств мальдеброта
#include <complex>
#include <iostream>
#include <thread>
#include <vector>
#include "boost/asio"
#include <SFML/Graphics.hpp>
future incl
#include <SFML/Graphics.hp>
class Calculator
{
public:

    using field_t = std::vector < std::vector < std::size_t > > ;

public:

    explicit Calculator(std::size_t width, std::size_t height, std::size_t max_iterations) ://шарина высота макс итераций
		m_width(width), m_height(height), m_max_iterations(max_iterations),m_tp(std::thread::hardware_concurrency())
	{
		initialize();
	}

	~Calculator() noexcept = default;

private:

	void initialize();

public:

    const auto & field() const noexcept 
	{ 
		return m_field; 
	}

	const auto width () const noexcept 
	{ 
		return m_width;  
	}

	const auto height() const noexcept 
	{ 
		return m_height; 
	}

	const auto max_iterations() const noexcept 
	{ 
		return m_max_iterations; 
	}

public:

	void calculate(sf::Vector2f center, float width, float height);//выполняет расчет

private:

	std::size_t m_width;
	std::size_t m_height;

    std::size_t m_max_iterations;

	field_t m_field;//двумерный массив() рабочая область разбиыается на какой-то кол-во клеток в каждую клетку записываем кол-во итерация
	//100 итераций- черная клетка
	boost asio thread pool??

};