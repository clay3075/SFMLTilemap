//
// Created by Clay Reddick on 2/10/21.
//

#include <iostream>
#include "UIStack.h"

void UIStack::reposition() {
    int positionX = _position.x;
    int positionY = _position.y;

    for (auto element : _elements) {
        Point tmp = element->getPosition();
        if (_stackDirection == Horizontal) {
            tmp.x = positionX;
            tmp.y = _position.y;
        } else {
            tmp.x = _position.x;
            tmp.y = positionY;
        }

        element->setPosition(tmp);

        auto dim = element->getDimensions();
        positionX += dim.width + _padding;
        positionY += dim.height + _padding;
    }
}

void UIStack::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto element : _elements) {
        element->draw(target, states);
    }
}

void UIStack::update(sf::Event event) {
    for(auto element : _elements) {
        element->update(event);
    }
}

void UIStack::insert(UIElement* element) {
    _elements.push_back(element);
    reposition();
}

Dimensions UIStack::getDimensions() {
    UIElement::getDimensions();

    Dimensions dim;

    for (auto element : _elements) {
        if (_stackDirection == Horizontal) {
            dim.width += element->getDimensions().width + _padding;
            if (element->getDimensions().height > dim.height)
                dim.height = element->getDimensions().height;
        } else {
            dim.height += element->getDimensions().height + _padding;
            if (element->getDimensions().width > dim.width)
                dim.width = element->getDimensions().width;
        }
    }

    return dim;
}

UIStack::~UIStack() {
    for (auto element : _elements) {
        delete element;
    }
}

void UIStack::remove(UIElement *element) {
    auto removeAt = std::find(_elements.begin(), _elements.end(), element);
    if (removeAt != _elements.end()) {
        _elements.erase(removeAt);
    }
    reposition();
}
