#pragma once
#include <SFML/Graphics.hpp>

#include <vector>

#include "Container.hpp"
#include "Pipe.hpp"
#include "Constants.hpp"
#include "Bird.hpp"

using namespace std;

class Game
{
	private:
		vector<Pipe*> Pipes;
		vector<Pipe*> DeadPipes;
		vector<Bird*> Birds;

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
	Pipe::speed = Container::WindowWidth / 100;

	Bird::x = Container::WindowWidth / 10;
	Bird::height = Container::WindowHeight / 10;
	Bird::wight = Container ::WindowWidth / 15;

	Pipes = vector<Pipe*>();
	DeadPipes = vector<Pipe*>();
	Birds = vector<Bird*>();

	PipeSpawnTicker = 0.5f * FPS - 1;
	PipeSpawnDuration = 0.5f * FPS;

	Bird* bird = new Bird();
	Birds.push_back(bird);
}

void Game::Render()
{
	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Render();
	}

	for (size_t i = 0; i < DeadPipes.size(); i++)
	{
		DeadPipes[i]->Render();
	}
	

	for (size_t i = 0; i < Birds.size(); i++)
	{
		Birds[i]->Render();
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
		if (LeftOne->GetX() + Pipe::wight < Bird::x)
		{
			Pipes.erase(Pipes.begin());
			DeadPipes.push_back(LeftOne);
			LeftOne->Die();
		}
	}

	if (!DeadPipes.empty())
	{
		Pipe* LeftOne = DeadPipes[0];
		if (LeftOne->GetX() + Pipe::wight < 0)
		{
			DeadPipes.erase(DeadPipes.begin());
			delete LeftOne;
		}
	}

	for (size_t i = 0; i < Pipes.size(); i++)
	{
		Pipes[i]->Update();
	}

	for (size_t i = 0; i < DeadPipes.size(); i++)
	{
		DeadPipes[i]->Update();
	}
}

void Game::SpawnPipe()
{
	Pipe* newPipe = new Pipe(Container::WindowWidth, 0);
	Pipes.push_back(newPipe);
}


