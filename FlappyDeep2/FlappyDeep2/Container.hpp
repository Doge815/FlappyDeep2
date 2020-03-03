#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Container
{
	public:
		static RenderWindow* RenderWindow;
		static int WindowHeight;
		static int WindowWidth;
};

RenderWindow *Container::RenderWindow;
int Container::WindowHeight;
int Container::WindowWidth;