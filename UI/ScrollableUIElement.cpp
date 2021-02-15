//
// Created by Clay Reddick on 2/14/21.
//

#include "ScrollableUIElement.h"
#include "Dimensions.h"
#include "Point.h"
#include "UIElement.h"

UI::ScrollableUIElement::ScrollableUIElement(sf::RenderWindow *window, const UI::Dimensions &dim, const UI::Point &pos) : UIElement(window, dim, pos){
}

void UI::ScrollableUIElement::update(sf::Event event) {
//    auto tmpView = _window->getView();
    _window->setView(_view);

    UIElement::update(event);

    _canScroll = true;

    setViewPort(sf::FloatRect(_position.x, _position.y, _dimensions.width/_window->getSize().x, _dimensions.height/_window->getSize().y));

    auto pixelPos = sf::Mouse::getPosition(*_window);
    sf::Vector2f cursorPos = _window->mapPixelToCoords(pixelPos);

    if (_canScroll && (_scrollDirection == Horizontal || _scrollDirection == Both)) {
        if ((cursorPos.x > _window->getSize().x - _scrollBorder && cursorPos.x <= _window->getSize().x) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            _view.move(_scrollSpeed, 0);
        }
        if ((cursorPos.x >= 0 && cursorPos.x <  _scrollBorder ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
            _view.move(-_scrollSpeed, 0);
        }
    }
    if (_canScroll && (_scrollDirection == Vertical || _scrollDirection == Both)) {
        if ((cursorPos.y >= _window->getSize().y * .25 && cursorPos.y < _window->getSize().y * .25 + _scrollBorder ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
            _view.move(0, -_scrollSpeed);
        }
        if ((cursorPos.y > _window->getSize().y - _scrollBorder && cursorPos.y <= _window->getSize().y ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
            _view.move(0, _scrollSpeed);
        }
    }

//    _window->setView(tmpView);
}

void UI::ScrollableUIElement::setViewPort(const sf::FloatRect &viewPort) {
    _view.setViewport(viewPort);
}
