#include <SFML/Graphics.hpp>
#include "TileMapRenderer.h"
#include <iostream>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main()
{
    TileMap map("../map.txt");

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML Application");
    TileMapRenderer mapRenderer(&window, map);

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        mapRenderer.draw();
        window.display();
    }

    return 0;
}