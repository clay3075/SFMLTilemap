//
// Created by Clay Reddick on 2/9/21.
//

#include "Label.h"

Label::Label(sf::RenderWindow *window, const Dimensions &dim, const Point &position) : TextInput(window, dim, position) {
    setIsEditable(false);
    setBackgroundColor(sf::Color::Transparent);
    setTextColor(sf::Color::White);
}
