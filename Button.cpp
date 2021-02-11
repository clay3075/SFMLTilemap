//
// Created by Clay Reddick on 2/10/21.
//

#include <iostream>
#include "Button.h"

//template <class T>
//Button<T>::Button(sf::RenderWindow *window, const Dimensions &dim, const Point &position) : Label(window, dim, position) {}

//template <class T>
//void Button<T>::update(sf::Event event) {
//    TextInput::update(event);
//
//    if (_hover && _canClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//        _canClick = false;
//        setBorderThickness(2);
//        setBorderColor(_clickColor);
//        if (_onClick) _onClick();
//    } else if (_hover && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
//        _canClick = true;
//        setBorderThickness(2);
//        setBorderColor(_hoverColor);
//    } else {
//        setBorderThickness(0);
//    }
//}
//
//template <class T>
//void Button<T>::setBackgroundTexture(const sf::Texture texture) {
//    setBackgroundColor(sf::Color::White);
//    _backgroundTexture = texture;
//    _shape.setTexture(&_backgroundTexture);
//}
