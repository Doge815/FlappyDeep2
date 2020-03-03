#pragma once
//#include <SFML/Graphics.hpp>
#include "Container.hpp"
#include <vector>
#include "Pipe.hpp"
using namespace sf;
using namespace std;

class Game
{
	private:
		vector<Pipe*> Pipes;
	public:
		Game(RenderWindow* rw);
		void Render();
};

Game::Game(RenderWindow* rw)
{
	Container::RenderWindow = rw;
	Container::WindowHeight = rw->getSize().y;
	Container::WindowWidth = rw->getSize().x;

	Pipe::gap = Container::WindowHeight / 10;
	Pipe::height = Container::WindowHeight;
	Pipe::wight = Container::WindowWidth / 10;

	Pipes = vector<Pipe*>();
	Pipes.push_back(new Pipe(10, 0));
}

void Game::Render()
{
	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Render();
	}
}
