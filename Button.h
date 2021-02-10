//
// Created by Clay Reddick on 2/10/21.
//

#ifndef SFMLTILEMAP_BUTTON_H
#define SFMLTILEMAP_BUTTON_H
#include "Label.h"

class Button : public Label {
public:
    Button(sf::RenderWindow *window, const Dimensions &dim, const Point &position);
    void update(sf::Event event) override;
    void setOnClick(void (*onClick)()) { _onClick = onClick; }
    void setHoverColor(const sf::Color color) { _hoverColor = color; }
    void setClickColor(const sf::Color color) { _clickColor = color; }
    void setBackgroundTexture(sf::Texture texture);
private:
    void (*_onClick)() = nullptr;
    bool _canClick = true;
    sf::Color _hoverColor = sf::Color::Green;
    sf::Color _clickColor = sf::Color::Yellow;
    sf::Texture _backgroundTexture;
};


#endif //SFMLTILEMAP_BUTTON_H
