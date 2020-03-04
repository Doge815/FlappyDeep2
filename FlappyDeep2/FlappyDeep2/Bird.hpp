#pragma once
#include <SFML/Graphics.hpp>

#include "Container.hpp"
#include "Pipe.hpp"

class Bird
{
    private:
        int y;
        int Jumpheight;
        bool colliding;
        sf::RectangleShape* rs;
        void Die();
    public:
        static int wight;
		static int height;
        static int x;

        static const int gravity = 2;
        static const int jumpPower = 25;

        Bird();
        ~Bird();
        void Jump();
        void Update();
        void Render();
        void NoCollision();
        void CollisionCheck(Pipe* pipe);
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
    Jumpheight = 0;
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
    if(Jumpheight < jumpPower * 4 / 5)
    Jumpheight = jumpPower;
}

void Bird::CollisionCheck(Pipe* pipe)
{
    colliding = false;
    if(y + height > pipe->GetY() + pipe->gap || y < pipe->GetY() - pipe->gap)
    {
        colliding = true;
        Die();
    }
}

void Bird::Update()
{
    y -= Jumpheight;
    Jumpheight -= gravity;
}

void Bird::Die()
{
    Game::GetCurrentGame()->Deadbirds.push_back(this);
}

int Bird::wight;
int Bird::height;
int Bird::x;

   

