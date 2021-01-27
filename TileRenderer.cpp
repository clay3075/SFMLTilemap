//
// Created by Clay Reddick on 1/26/21.
//

#include <iostream>
#include "TileRenderer.h"

void TileRenderer::draw() {
    sf::Sprite sprite;
    sf::Texture texture;
    Dimensions tileDim = _tile.getDimensions();
    Point tilePos = _tile.getPosition();
    int spriteX = tilePos.x * tileDim.width;
    int spriteY = tilePos.y * tileDim.height;

    if (!texture.loadFromFile(_tile.getTexturePath()))
    {
        std::cout << "Failed to load texture";
    }

    sprite.setTexture(texture);
    sprite.setPosition(spriteX, spriteY);
    double textureWidth = texture.getSize().x;
    double textureHeight = texture.getSize().y;
    sprite.setScale(tileDim.width/textureWidth, tileDim.height/textureHeight);
    _window->draw(sprite);
}
