//
// Created by Clay Reddick on 2/10/21.
//

#ifndef SFMLTILEMAP_UISTACK_H
#define SFMLTILEMAP_UISTACK_H
#include "UIElement.h"
#include "ScrollableUIElement.h"
#include "Dimensions.h"
#include "Point.h"
#include <vector>
#include <iostream>

enum UIStackDirection {
    Horizontal,
    Vertical
};

namespace UI {
    class UIStack : public UI::UIElement {
    public:
        UIStack(UIStackDirection stackDirection, Point position = Point()) : UIElement(nullptr, Dimensions(), position) {
            _stackDirection = stackDirection;
        }
        void insert(UIElement* element);
        void remove(UIElement* element, bool freeMemory = true);
        void update(sf::Event event) override;
        void update() override;
        void setPadding(int padding) { _padding = padding; }
        void reposition() override;
        Dimensions getDimensions() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        std::vector<UIElement*>& getUIElements() { return _elements; }
        ~UIStack() override;

    protected:
        std::vector<UIElement*> _elements;
        UIStackDirection _stackDirection;
        int _padding = 0;
    };
}


#endif //SFMLTILEMAP_UISTACK_H
