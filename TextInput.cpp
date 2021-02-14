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

    if (_isEditable && _hasFocus && event.type == sf::Event::TextEntered) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
            _text.pop_back();
        } else if (event.text.unicode < 128 && event.text.unicode != 10) {
            _text += event.text.unicode;
        }

        resizeText();
    }
}

void TextInput::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(_shape);
    target.draw(_sfText);
}

void TextInput::positionText() {
    float x = _shape.getPosition().x;
    float y = _shape.getPosition().y;
    int charWidthSize = _text.size() * _sfText.getCharacterSize() * .5;

    switch (_textAlignment) {
        case TopLeft:
            //do nothing;
            break;
        case TopCenter:
            x += getDimensions().width / 2.0 - charWidthSize / 2.0;
            break;
        case TopRight:
            x += getDimensions().width - charWidthSize;
            break;
        case Left:
            y -= getDimensions().height / 2.0 - _sfText.getCharacterSize()/2.0;
            break;
        case Center:
            y -= getDimensions().height / 2.0 - _sfText.getCharacterSize()/2.0;
            x += getDimensions().width / 2.0 - charWidthSize / 2.0;
            break;
        case Right:
            y -= getDimensions().height / 2.0 - _sfText.getCharacterSize()/2.0;
            x += getDimensions().width - charWidthSize;;
        case BottomLeft:
            y -= getDimensions().height - _sfText.getCharacterSize();
            break;
        case BottomCenter:
            y -= getDimensions().height - _sfText.getCharacterSize();
            x += getDimensions().width / 2.0 - _sfText.getCharacterSize()/2.0;
            break;
        case BottomRight:
            y -= getDimensions().height - _sfText.getCharacterSize();
            x += getDimensions().width - charWidthSize;
            break;
    }

    _sfText.setPosition(x, y);
}

void TextInput::resizeText() {

    while (_text.size() * _sfText.getCharacterSize()*.55 > _shape.getSize().x) {
        _text.pop_back();
    }

    positionText();
    _sfText.setString(_text);
}

void TextInput::reposition() {
    _shape.setPosition(_position.x, _position.y);
    positionText();
}
