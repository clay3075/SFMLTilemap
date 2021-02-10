//
// Created by Clay Reddick on 2/9/21.
//

#include <iostream>
#include "UIElement.h"

UIElement::UIElement(sf::RenderWindow* window, Dimensions dim, Point pos) {
    if (!_font.loadFromFile("../default.ttf"))
    {
        std::cout << "Error loading font";
    }

    _window = window;
    _dimensions = dim;
    _position = pos;
}

void UIElement::update(sf::Event event) {
    auto pixelPos = sf::Mouse::getPosition(*_window);
    sf::Vector2f cursorPos = _window->mapPixelToCoords(pixelPos);

    if (cursorPos.x > _position.x && cursorPos.x < _position.x+_dimensions.width &&
        cursorPos.y > _position.y && cursorPos.y < _position.y+_dimensions.height) {
        _hover = true;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            _hasFocus = true;
    } else {
        _hover = false;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            _hasFocus = false;
    }
}
