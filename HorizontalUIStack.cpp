//
// Created by Clay Reddick on 2/10/21.
//

#include <iostream>
#include "HorizontalUIStack.h"

void HorizontalUIStack::reposition() {
    int positionX = _position.x;
    for (auto element : _elements) {
        Point tmp = element->getPosition();
        tmp.x = positionX;
        tmp.y = _position.y;
        element->setPosition(tmp);
        positionX += element->getDimensions().width + _padding;
    }
}

void HorizontalUIStack::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto element : _elements) {
        element->draw(target, states);
    }
}

void HorizontalUIStack::update(sf::Event event) {
    for(auto element : _elements) {
        element->update(event);
    }
}

void HorizontalUIStack::insert(std::shared_ptr<UIElement> element) {
    _elements.push_back(element);
    reposition();
}
