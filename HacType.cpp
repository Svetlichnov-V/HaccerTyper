#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include "String.h"
#include "SFML/Graphics.hpp"
#include <stdio.h>

int handlingEvent(sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			return 0;
		}
		if (event.type == sf::Event::KeyReleased)
		{
			return 1;
		}
	}
}

int FileLen(FILE* file)
{
	assert(file);          //??????
	fseek(file, 0, SEEK_END);
	int lenf = ftell(file);
	fseek(file, 0, SEEK_SET);
	return lenf;
}

int main()
{
	FILE* code = fopen("Text.txt", "r");
	int sizeCode = FileLen(code);

	//std::cout << sizeCode << std::endl;

	String buffer("", sizeCode);
	int pointer = 0;
	int a = fread(buffer.str, sizeof(char), sizeCode, code);
	fclose(code);

	//std::cout << buffer << std::endl;
	//std::cout << a << std::endl;

	String visCode("", sizeCode);

	sf::Font font; 
	font.loadFromFile("CyrilicOld.ttf");
	sf::Text visible;
	visible.setFont(font);
	visible.setFillColor(sf::Color::Green);
	visible.setOutlineColor(sf::Color::Green);
	visible.setPosition(50, 50);

	const int X_MAX = 1960;
	const int Y_MAX = 1080;

	sf::Color fillColor = sf::Color(10, 10, 100);
	sf::RenderWindow window(sf::VideoMode(X_MAX, Y_MAX), "Main window");
	window.setFramerateLimit(60);
	window.clear(fillColor);
	window.display();

	int numberOfFirstStrInVisible = -33;
	int bies = 0;

	//std::cout << 1 << std::endl;

	while (true)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::KeyReleased)
			{
				visCode += buffer[pointer];
				visCode += buffer[pointer + 1];
				visCode += buffer[pointer + 2];

				//std::cout << numberOfFirstStrInVisible << std::endl;

				if (buffer[pointer] == '\n')
					numberOfFirstStrInVisible += 1;
				if (buffer[pointer + 1] == '\n')
					numberOfFirstStrInVisible += 1;
				if (buffer[pointer + 2] == '\n')
					numberOfFirstStrInVisible += 1;

				pointer += 3;
			}
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				{
					int a = event.mouseWheelScroll.delta;
					//std::cout << a << std::endl;
					numberOfFirstStrInVisible -= a;
					//std::cout << 1 << std::endl;
				}
			}
		}
		
		if (numberOfFirstStrInVisible > 0)
		{
			int n = numberOfFirstStrInVisible;
			for (int i = 0; i < visCode.strSize; ++i)
			{
				if (visCode[i] == '\n')
					n -= 1;
				if (n == 0)
				{
					bies = i;
					break;
				}
				if (i == visCode.strSize - 1)
					bies = i;
			}
		}
		else
		{
			bies = 0;
		}

		//std::cout << numberOfFirstStrInVisible << ' ' << bies << std::endl;
		visible.setString(visCode.str + sizeof(char) * bies);
		//std::cout << visCode << std::endl;
		//std::cout << std::endl;

		window.clear(fillColor);
		window.draw(visible);
		window.display();
	}
	return 0;
}