#pragma once
#include <SFML/Graphics.hpp>
#include "Container.hpp"
using namespace sf;

class Pipe
{
	private:
		int x;
		int y;
		RectangleShape* rs;

	public:
		static int wight;
		static int height;
		static int speed;
		static int gap;

		void Render();
		Pipe(int X, int Y);
};

void Pipe::Render()
{
	rs->setPosition(x, y + gap + Container::WindowHeight / 2);
	Container::RenderWindow->draw(*rs);
	rs->setPosition(x, y - gap + Container::WindowHeight / 2 - height);
	Container::RenderWindow->draw(*rs);
}

Pipe::Pipe(int X, int Y)
{
	x = X;
	y = Y;
	rs = new RectangleShape();
	rs->setSize(Vector2f(wight, height));
	rs->setFillColor(Color::Green);
}

int Pipe::wight;
int Pipe::height;
int Pipe::gap;
int Pipe::speed;