//
// Created by Clay Reddick on 2/9/21.
//

#ifndef SFMLTILEMAP_TEXTINPUT_H
#define SFMLTILEMAP_TEXTINPUT_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Dimensions.h"
#include "Point.h"
#include "UIElement.h"

class TextInput : public UIElement {
public:
    TextInput(sf::RenderWindow* window, Dimensions dim, Point position);
    void update(sf::Event event) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    std::string _text;
    sf::RectangleShape _shape;
    sf::Text _sfText;
};


#endif //SFMLTILEMAP_TEXTINPUT_H
