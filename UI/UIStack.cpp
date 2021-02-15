//
// Created by Clay Reddick on 2/10/21.
//

#include <iostream>
#include "UIStack.h"
#include "Dimensions.h"
#include "Point.h"
#include "UIElement.h"

void UI::UIStack::reposition() {
    int positionX = _position.x;
    int positionY = _position.y;

    for (auto element : _elements) {
        UI::Point tmp = element->getPosition();
        if (_stackDirection == UIStackDirection::Horizontal) {
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

void UI::UIStack::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    for(auto element : _elements) {
        element->draw(target, states);
    }
}

void UI::UIStack::update(sf::Event event) {

    for(auto element : _elements) {
        element->update(event);
    }
}

void UI::UIStack::insert(UIElement* element) {
    _elements.push_back(element);
    reposition();
}

UI::Dimensions UI::UIStack::getDimensions() {
    UI::UIElement::getDimensions();

    UI::Dimensions dim;

    for (auto element : _elements) {
        if (_stackDirection == UIStackDirection::Horizontal) {
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

UI::UIStack::~UIStack() {
    for (auto element : _elements) {
        remove(element, true);
    }
}

void UI::UIStack::remove(UIElement *element, bool freeMemory) {
    auto removeAt = std::find(_elements.begin(), _elements.end(), element);
    if (removeAt != _elements.end()) {
        if (freeMemory && *removeAt) delete *removeAt;
        _elements.erase(removeAt);

        reposition();
    }
}

void UI::UIStack::update() {
    UI::UIElement::update();

    for(auto element : _elements) {
        element->update();
    }
}
