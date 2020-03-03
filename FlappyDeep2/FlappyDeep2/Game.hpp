#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "Container.hpp"
#include "Pipe.hpp"
#include "Constants.hpp"

using namespace std;

class Game
{
	private:
		vector<Pipe*> Pipes;

		int PipeSpawnDuration;
		int PipeSpawnTicker;

		void SpawnPipe();
	public:
		Game(sf::RenderWindow* rw);
		void Render();
		void Update();
		
};

Game::Game(sf::RenderWindow* rw)
{
	Container::RenderWindow = rw;
	Container::WindowHeight = rw->getSize().y;
	Container::WindowWidth = rw->getSize().x;

	Pipe::gap = Container::WindowHeight / 10;
	Pipe::height = Container::WindowHeight;
	Pipe::wight = Container::WindowWidth / 10;
	Pipe::speed = 5;

	Pipes = vector<Pipe*>();

	PipeSpawnTicker = 2 * FPS - 1;
	PipeSpawnDuration = 2 * FPS;
}

void Game::Render()
{
	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Render();
	}
}

void Game::Update()
{
	PipeSpawnTicker++;
	if (PipeSpawnTicker == PipeSpawnDuration)
	{
		PipeSpawnTicker = 0;
		Game::SpawnPipe();
	}
	if (!Pipes.empty())
	{
		Pipe* LeftOne = Pipes[0];
		if (LeftOne->GetX() + Pipe::wight < 0)
		{
			Pipes.erase(Pipes.begin());
			delete LeftOne;
		}
	}

	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Update();
	}
}

void Game::SpawnPipe()
{
	Pipe* newPipe = new Pipe(Container::WindowWidth, 0);
	Pipes.push_back(newPipe);
}


