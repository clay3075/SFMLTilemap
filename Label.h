//
// Created by Clay Reddick on 2/9/21.
//

#ifndef SFMLTILEMAP_LABEL_H
#define SFMLTILEMAP_LABEL_H
#include <SFML/Graphics.hpp>
#include "TextInput.h"

class Label : public TextInput {
public:
    Label(sf::RenderWindow *window, const Dimensions &dim, const Point &position = Point());
};


#endif //SFMLTILEMAP_LABEL_H
