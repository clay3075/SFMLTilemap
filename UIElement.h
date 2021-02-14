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
    explicit UIElement(sf::RenderWindow* window, Dimensions dim = Dimensions(), Point pos = Point());
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override {};
    void setPosition(Point position) { _position = position; reposition(); }
    Point getPosition() { return _position; }
    void setDimensions(Dimensions dimensions) { _dimensions = dimensions; }
    virtual void reposition() = 0;

    virtual Dimensions getDimensions() { return _dimensions; }
    virtual void update(sf::Event event);
    virtual void update() {}
protected:
    sf::Font _font;
    sf::RenderWindow* _window;
    bool _hasFocus = false;
    bool _hover = false;
    Dimensions _dimensions;
    Point _position;
};


#endif //SFMLTILEMAP_UIELEMENT_H
