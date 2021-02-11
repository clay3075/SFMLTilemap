//
// Created by Clay Reddick on 2/10/21.
//

#ifndef SFMLTILEMAP_BUTTON_H
#define SFMLTILEMAP_BUTTON_H
#include "Label.h"

template <class T>
class Button : public Label {
public:
    Button(sf::RenderWindow *window, const Dimensions &dim, const Point &position = Point()) : Label(window, dim, position) {};
    void update(sf::Event event) override {
        TextInput::update(event);

        if (_hover && _canClick && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _canClick = false;
            setBorderThickness(2);
            setBorderColor(_clickColor);
            if (_onClick) _onClick();
        } else if (_hover && !sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            _canClick = true;
            setBorderThickness(2);
            setBorderColor(_hoverColor);
        } else {
            setBorderThickness(0);
        }
    }
//    void setOnClick(void (T::*onClick)()) { _onClick = onClick; }
    void setOnClick(std::function<void()> onClick) { _onClick = onClick; }
    void setHoverColor(const sf::Color color) { _hoverColor = color; }
    void setClickColor(const sf::Color color) { _clickColor = color; }
    void setBackgroundTexture(sf::Texture texture) {
        setBackgroundColor(sf::Color::White);
        _backgroundTexture = texture;
        _shape.setTexture(&_backgroundTexture);
    }
private:
//    void (T::*_onClick)() = nullptr;
    std::function<void()> _onClick = nullptr;
    bool _canClick = true;
    sf::Color _hoverColor = sf::Color::Green;
    sf::Color _clickColor = sf::Color::Yellow;
    sf::Texture _backgroundTexture;
};


#endif //SFMLTILEMAP_BUTTON_H
