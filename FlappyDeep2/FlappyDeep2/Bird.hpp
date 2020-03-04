#pragma once
#include <SFML/Graphics.hpp>

#include "Container.hpp"

class Bird
{
    private:
        int y;
        sf::RectangleShape* rs;
    public:
        static int wight;
		static int height;
        static int x;

        Bird();
        ~Bird();
        void Jump();
        void Update();
        void Render();
};

void Bird::Render()
{
    rs->setPosition(x, y);
    Container::RenderWindow->draw(*rs);
}

Bird::Bird()
{
    y = (Container::WindowHeight - height) / 2;
    rs = new RectangleShape();
    rs->setSize(Vector2f(wight, height));
    rs->setFillColor(Color::Red);
}

Bird::~Bird()
{
    //Todo: Cleanup
}

int Bird::wight;
int Bird::height;
int Bird::x;

   

