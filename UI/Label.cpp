//
// Created by Clay Reddick on 2/9/21.
//

#include "Label.h"
#include "Dimensions.h"
#include "Point.h"
#include "TextInput.h"

UI::Label::Label(sf::RenderWindow *window, const UI::Dimensions &dim, const Point &position) : TextInput(window, dim, position) {
    setIsEditable(false);
    setBackgroundColor(sf::Color::Transparent);
    setTextColor(sf::Color::White);
}
