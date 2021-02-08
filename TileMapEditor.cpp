//
// Created by Clay Reddick on 2/7/21.
//

#include <iostream>
#include "TileMapEditor.h"

TileMapEditor::TileMapEditor(sf::RenderWindow *window)  {
    _window = window;
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

