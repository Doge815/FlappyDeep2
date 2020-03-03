#include <SFML/Graphics.hpp>

#include "Game.h"
#include "Constants.hpp"

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Size, Size), "FlappyDeep2", sf::Style::Titlebar | sf::Style::Close);

    Game g = Game(window);
    window->setFramerateLimit(FPS);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color::Black);
        g.Update();
        g.Render();
        window->display();
    }

    return 0;
}