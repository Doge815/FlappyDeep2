#pragma once
#include <SFML/Graphics.hpp>

#include "Container.hpp"
#include "Pipe.hpp"

class Bird
{
    private:
        int y;
        int Jumpheight = 0;
        bool colliding;
        sf::RectangleShape* rs;
    public:
        static int wight;
		static int height;
        static const int gravity = 3;
        static int x;

        Bird();
        ~Bird();
        void Jump();
        void Update();
        void Render();
        void NoCollision();
        void CollisionCheck(Pipe* pipe);
        void Jump();
};

void Bird::Render()
{
    rs->setPosition(x, y + Container::WindowHeight / 2);
    rs->setFillColor(colliding ? Color::Red : Color::White);
    Container::RenderWindow->draw(*rs);
}

Bird::Bird()
{
    colliding = false;
    y = 0 - height / 2;
    rs = new RectangleShape();
    rs->setSize(Vector2f(wight, height));
    rs->setFillColor(Color::Red);
} 

Bird::~Bird()
{
    //Todo: Cleanup
}

void Bird::NoCollision()
{
    colliding = false;
}

void Bird::Jump()
{
    Jumpheight = 10;
}

void Bird::CollisionCheck(Pipe* pipe)
{
    colliding = false;
    if(y + height > pipe->GetY() + pipe->gap || y < pipe->GetY() - pipe->gap)
    {
        colliding = true;
    }
}

int Bird::wight;
int Bird::height;
int Bird::x;

   

