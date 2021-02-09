//
// Created by Clay Reddick on 2/7/21.
//

#include <iostream>
#include "TileMapEditor.h"

TileMapEditor::TileMapEditor(sf::RenderWindow *window)  {
    _window = window;
    _tileView.zoom(1);
    _tileView.setViewport(sf::FloatRect(0.0f, .25f, 1, 1));
    _window->setView(_tileView);

    initMap();
    auto texture = new sf::Texture;
    if (!texture->loadFromFile("../ground.png")) {
        std::cout << "Error\n";
    }
    _textures.insert({0, texture});
    _selectedTexture = texture;
}

void TileMapEditor::initMap() {
    for (int r = 0; r < _rows; r++) {
        _tiles.push_back(std::vector<BuilderTile*>());
        for (int c = 0; c < _columns; c++) {
            auto point = Point(c, r);
            auto tile = new BuilderTile(_tileDimensions, point);

            tile->setTexture(nullptr);
            _tiles[r].push_back(tile);
        }
    }
}

void TileMapEditor::update() {
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _columns; c++) {
            _tiles[r][c]->update(_window, _selectedTexture);
        }
    }
    auto pixelPos = sf::Mouse::getPosition(*_window);
    if ((pixelPos.x > _window->getSize().x - _panBorder && pixelPos.x <= _window->getSize().x) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _tileView.move(_panSpeed, 0);
        _window->setView(_tileView);
    } else if ((pixelPos.x >= 0 && pixelPos.x <  _panBorder ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
        _tileView.move(-_panSpeed, 0);
        _window->setView(_tileView);
    } else if ((pixelPos.y >= _window->getSize().y*.25 && pixelPos.y < _window->getSize().y*.25 + _panBorder ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
        _tileView.move(0, _panSpeed);
        _window->setView(_tileView);
    } else if ((pixelPos.y > _window->getSize().y - _panBorder && pixelPos.y <= _window->getSize().y ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
        _tileView.move(0, -_panSpeed);
        _window->setView(_tileView);
    }
}

void TileMapEditor::draw() {
    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _columns; c++) {
            _window->draw(*_tiles[r][c]);
        }
    }
}

void TileMapEditor::clearMap() {
    for (int r = 0; r < _rows; r++) {
        _tiles.push_back(std::vector<BuilderTile*>());
        for (int c = 0; c < _columns; c++) {
            delete _tiles[r][c];
        }
    }
    _tiles.clear();
}

TileMapEditor::~TileMapEditor() {
    clearMap();
    clearTextures();
}

void TileMapEditor::clearTextures() {
    for (auto textureMap : _textures) {
        delete textureMap.second;
    }
    _textures.clear();
}

