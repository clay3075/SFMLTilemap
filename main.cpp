#include <SFML/Graphics.hpp>
#include "TileMapRenderer.h"
#include "TileMapEditor.h"
#include <iostream>
#include "TextInput.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tilemap Editor");
    window.setFramerateLimit(60);
//    TileMapEditor editor(&window);
    TextInput input(&window, Dimensions(100, 50), Point(0, 0));
    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            input.update(event);
        }

//        editor.update();

        window.clear();
//        editor.draw();
window.draw(input);
        window.display();
    }

    return 0;
}