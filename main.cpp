#include <SFML/Graphics.hpp>
#include "TileMapRenderer.h"
#include "TileMapEditor.h"
#include <iostream>
#include "TextInput.h"
#include "Label.h"
#include "Button.h"
#include "HorizontalUIStack.h"
#include <memory>

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Tilemap Editor");
    window.setFramerateLimit(60);
//    TileMapEditor editor(&window);
    std::shared_ptr<Button> input = std::make_shared<Button>(Button(&window, Dimensions(64, 64), Point()));
    std::shared_ptr<Button> input2 = std::make_shared<Button>(Button(&window, Dimensions(64, 64), Point()));
    std::shared_ptr<Button> input3 = std::make_shared<Button>(Button(&window, Dimensions(64, 64), Point()));
    sf::Texture texture;
    texture.loadFromFile("../image.png");
    input->setBackgroundTexture(texture);
    input2->setBackgroundTexture(texture);
    input3->setBackgroundTexture(texture);
    HorizontalUIStack stack(Dimensions(SCREEN_WIDTH, 64), Point(5, 5));
    stack.insert(input);
    stack.insert(input2);
    stack.insert(input3);


    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            stack.update(event);
        }

//        editor.update();

        window.clear();
//        editor.draw();
window.draw(stack);
        window.display();
    }

    return 0;
}