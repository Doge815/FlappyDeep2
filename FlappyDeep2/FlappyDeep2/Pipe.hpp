#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Pipe
{
	private:
		int x;
		int y;
		RectangleShape* rs;

	public:
		static const int wight = 20;
		static const int height = 50;
		static int speed;
		static int gap;
		void Draw(RenderWindow* rf);
		Pipe(int X, int Y);
};

void Pipe::Draw(RenderWindow* rf)
{
	rf->draw(*rs);
}

Pipe::Pipe(int X, int Y)
{
	x = X;
	y = Y;
	rs = new RectangleShape()
}