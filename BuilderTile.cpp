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
        _sprite.setFillColor(sf::Color::Black);
    }

    auto size = sf::Vector2<float>(_dimensions.width, _dimensions.height);
    _sprite.setSize(size);
    _sprite.setPosition(_dimensions.width*_point.x, _dimensions.height*_point.y);
}

void BuilderTile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(_sprite);
}

void BuilderTile::mouseEnter(sf::Texture* texture) {
    _mouseCaptured = true;
    _tmpTexture = _currentTexture;
    _currentTexture = texture;

    if (_currentTexture) {
        setTexture(_currentTexture);
    }
    else {
        _sprite.setFillColor(sf::Color::White);
        _tmpTexture = nullptr;
        _currentTexture = nullptr;
    }
}

void BuilderTile::mouseExit() {
    if (_mouseCaptured) {
        if (_textureChanged) {
            setTexture(_currentTexture);
        } else {
            setTexture(nullptr);
            _tmpTexture = nullptr;
            _currentTexture = nullptr;
        }
        _mouseCaptured = false;
        _textureChanged = false;
    }
}

void BuilderTile::update(sf::RenderWindow* window, sf::Texture* texture) {
    auto cursorPos = sf::Mouse::getPosition(*window);
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
