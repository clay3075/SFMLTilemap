//
// Created by Clay Reddick on 2/14/21.
//

#ifndef SFMLTILEMAP_SCROLLABLEUIELEMENT_H
#define SFMLTILEMAP_SCROLLABLEUIELEMENT_H
#include <SFML/Graphics.hpp>
#include "UIElement.h"
#include "Dimensions.h"
#include "Point.h"


namespace UI {
    class ScrollableUIElement : public UIElement {
    public:
        ScrollableUIElement(sf::RenderWindow *window, const Dimensions &dim = Dimensions(), const Point &pos = Point());
        void update(sf::Event event) override;
        void setViewPort(const sf::FloatRect &viewPort);
        enum ScrollDirection {
            Both,
            Horizontal,
            Vertical
        };
    private:
        sf::View _view;
        int _scrollBorder = 10;
        int _scrollSpeed = 5;
        bool _canScroll;
        ScrollDirection _scrollDirection = Both;
    };
}


#endif //SFMLTILEMAP_SCROLLABLEUIELEMENT_H
