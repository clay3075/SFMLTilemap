//
// Created by Clay Reddick on 2/10/21.
//

#ifndef SFMLTILEMAP_HORIZONTALUISTACK_H
#define SFMLTILEMAP_HORIZONTALUISTACK_H
#include "UIElement.h"
#include <vector>

class HorizontalUIStack : public sf::Drawable {
public:
    HorizontalUIStack(Dimensions dim, Point position) {
        _dimensions = dim;
        _position = position;
    }
    void insert(std::shared_ptr<UIElement> element);
    void update(sf::Event event);
    void setPadding(int padding) { _padding = padding; }
    void reposition();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    std::vector<std::shared_ptr<UIElement>> _elements;
    Dimensions _dimensions;
    Point _position;
    int _padding = 0;
};


#endif //SFMLTILEMAP_HORIZONTALUISTACK_H
