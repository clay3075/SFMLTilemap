//
// Created by Clay Reddick on 2/7/21.
//

#include <iostream>
#include "BuilderTile.h"

void BuilderTile::setCollision(bool collision) { _collision = collision; }

void BuilderTile::setTexture(sf::Texture* texture) {
    if (texture) {
        _sprite.setFillColor(sf::Color::White);
        _sprite.setTexture(texture);
        _sprite.setScale(_dimensions.width/(float)texture->getSize().x, _dimensions.height/(float)texture->getSize().y);
    } else {
        _sprite.setFillColor(sf::Color::White);
        _sprite.setTexture(nullptr);
    }

    auto size = sf::Vector2<float>(_dimensions.width, _dimensions.height);
    _sprite.setSize(size);
    _sprite.setPosition(_dimensions.width*_point.x, _dimensions.height*_point.y);
}

void BuilderTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite);
}

void BuilderTile::mouseEnter(sf::Texture* texture) {
    if (!_mouseCaptured) {
        _mouseCaptured = true;
        _oldTexture = _currentTexture;
        _currentTexture = texture;
        setTexture(_currentTexture);
    }
}

void BuilderTile::mouseExit() {
    if (_mouseCaptured) {
        if (!_textureChanged) {
            _currentTexture = _oldTexture;
            setTexture(_currentTexture);
        }
        _mouseCaptured = false;
        _textureChanged = false;
        _oldTexture = nullptr;
    }
}

void BuilderTile::update(sf::RenderWindow* window, sf::Texture* texture) {
    auto pixelPos = sf::Mouse::getPosition(*window);
    sf::Vector2f cursorPos = window->mapPixelToCoords(pixelPos);

    if (cursorPos.x > _point.x*_dimensions.width && cursorPos.x < _point.x*_dimensions.width+_dimensions.width &&
            cursorPos.y > _point.y*_dimensions.height && cursorPos.y < _point.y*_dimensions.height+_dimensions.height) {
        mouseEnter(texture);
    } else {
        mouseExit();
    }

    if (_mouseCaptured && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        _textureChanged = true;
    }
}
