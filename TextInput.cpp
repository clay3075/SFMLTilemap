//
// Created by Clay Reddick on 2/9/21.
//

#include <iostream>
#include "TextInput.h"

TextInput::TextInput(sf::RenderWindow *window, Dimensions dim, Point position) : UIElement(window, dim, position) {
    _shape.setSize(sf::Vector2f(dim.width, dim.height));
    _shape.setPosition(position.x, position.y);
    _shape.setFillColor(sf::Color::White);

    _sfText.setCharacterSize(_shape.getSize().y*.9f);
    _sfText.setPosition(_shape.getPosition().x, _shape.getPosition().y+_shape.getSize().y*.025f);
    _sfText.setFillColor(sf::Color::Black);
    _sfText.setFont(_font);
}

void TextInput::update(sf::Event event) {
    UIElement::update(event);

    if (_hasFocus && event.type == sf::Event::TextEntered) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            _text.pop_back();
        } else if (event.text.unicode < 128)
        {
            _text += event.text.unicode;
        }
        _sfText.setString(_text);
    }
}

void TextInput::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_shape);
    target.draw(_sfText);
}
