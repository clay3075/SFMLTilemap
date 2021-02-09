//
// Created by Clay Reddick on 2/9/21.
//

#ifndef SFMLTILEMAP_UIELEMENT_H
#define SFMLTILEMAP_UIELEMENT_H
#include <SFML/Graphics.hpp>
#include "Dimensions.h"
#include "Point.h"

class UIElement : public sf::Drawable {
public:
    UIElement(sf::RenderWindow* window, Dimensions dim, Point pos);
    virtual void update(sf::Event event);
protected:
    sf::Font _font;
    sf::RenderWindow* _window;
    bool _hasFocus = false;
    Dimensions _dimensions;
    Point _position;
};


#endif //SFMLTILEMAP_UIELEMENT_H
