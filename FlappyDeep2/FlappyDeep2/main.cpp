#include <SFML/Graphics.hpp>

const int size = 500;

int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(size, size), "FlappyDeep2", sf::Style::Titlebar | sf::Style::Close);

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }

        window->clear(sf::Color::Black);
        window->display();
    }

    return 0;
}