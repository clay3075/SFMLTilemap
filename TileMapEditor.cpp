//
// Created by Clay Reddick on 2/7/21.
//

#include <iostream>
#include "TileMapEditor.h"
#include "Label.h"
#include "UIStack.h"

TileMapEditor::TileMapEditor(sf::RenderWindow *window)  {
    _window = window;

    _tileView.zoom(1);
    _tileView.setViewport(sf::FloatRect(0.0f, .25f, 1, 1));
    _window->setView(_tileView);

    _uiView.zoom(1);
    _uiView.setViewport(sf::FloatRect(0, 0, 1, 1));

    initMap();
    auto texture = new sf::Texture;
    if (!texture->loadFromFile("../ground.png")) {
        std::cout << "Error\n";
    }
    _textures.insert({0, texture});
    _selectedTexture = texture;

    _dimensionStack = new UIStack(Horizontal);
    _dimensionStack->setPadding(10);
    _widthInput =new TextInput(_window, Dimensions(120, 50));
    _widthInput->setText(std::to_string(_tileDimensions.width));
    _heightInput = new TextInput(_window, Dimensions(120, 50));
    _heightInput->setText(std::to_string(_tileDimensions.height));
    _xLabel = new Label(_window, Dimensions(30, 50));
    _xLabel->setBackgroundColor(sf::Color::Transparent);
    _xLabel->setTextColor(sf::Color::White);
    _xLabel->setText("X");
    _dimensionStack->insert(_widthInput);
    _dimensionStack->insert(_xLabel);
    _dimensionStack->insert(_heightInput);

    _gridDimLabelStack = new UIStack(Horizontal);
    _gridDimLabelStack->setPadding(50);
    _rowLabel = new Label(_window, Dimensions(120, 50));
    _rowLabel->setBackgroundColor(sf::Color::Transparent);
    _rowLabel->setTextColor(sf::Color::White);
    _rowLabel->setText("Rows");
    _columnLabel = new Label(_window, Dimensions(120, 50));
    _columnLabel->setBackgroundColor(sf::Color::Transparent);
    _columnLabel->setTextColor(sf::Color::White);
    _columnLabel->setText("Cols");
    _gridDimLabelStack->insert(_rowLabel);
    _gridDimLabelStack->insert(_columnLabel);

    _gridDimInputStack = new UIStack(Horizontal);
    _gridDimInputStack->setPadding(50);
    _rowInput = new TextInput(_window, Dimensions(120, 50));
    _rowInput->setText(std::to_string(_rows));
    _colInput = new TextInput(_window, Dimensions(120, 50));
    _colInput->setText(std::to_string(_columns));
    _gridDimInputStack->insert(_rowInput);
    _gridDimInputStack->insert(_colInput);

    _updateButton = new Button(_window, Dimensions(170, 50));
    _updateButton->setText("Update");

    _gridSettingsStack = new UIStack(Vertical, Point(5, 5));
    _gridSettingsStack->setPadding(5);
    _gridSettingsStack->insert(_dimensionStack);
    _gridSettingsStack->insert(_gridDimLabelStack);
    _gridSettingsStack->insert(_gridDimInputStack);
    _gridSettingsStack->insert(_updateButton);
}

void TileMapEditor::initMap() {
    for (int r = 0; r < _rows; r++) {
        _tiles.emplace_back();
        for (int c = 0; c < _columns; c++) {
            auto point = Point(c, r);
            auto tile = new BuilderTile(_tileDimensions, point);

            tile->setTexture(nullptr);
            _tiles[r].push_back(tile);
        }
    }
}

void TileMapEditor::update(sf::Event event) {
    updateTileView(event);
    updateUIView(event);
}

void TileMapEditor::draw() {
    drawTileView();
    drawUIView();
}

void TileMapEditor::clearMap() {
    for (int r = 0; r < _rows; r++) {
        _tiles.emplace_back();
        for (int c = 0; c < _columns; c++) {
            delete _tiles[r][c];
        }
    }
    _tiles.clear();
}

TileMapEditor::~TileMapEditor() {
    clearMap();
    clearTextures();

    delete _dimensionStack;
    delete _widthInput;
    delete _heightInput;
    delete _xLabel;

    delete _gridDimLabelStack;
    delete _rowLabel;
    delete _columnLabel;

    delete _gridDimInputStack;
    delete _rowInput;
    delete _colInput;

    delete _updateButton;

    delete _gridSettingsStack;
}

void TileMapEditor::clearTextures() {
    for (auto textureMap : _textures) {
        delete textureMap.second;
    }
    _textures.clear();
}

void TileMapEditor::updateTileView(sf::Event event) {
    _window->setView(_tileView);

    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _columns; c++) {
            _tiles[r][c]->update(_window, _selectedTexture);
        }
    }

    auto pixelPos = sf::Mouse::getPosition(*_window);
    if ((pixelPos.x > _window->getSize().x - _panBorder && pixelPos.x <= _window->getSize().x) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        _tileView.move(_panSpeed, 0);
    } else if ((pixelPos.x >= 0 && pixelPos.x <  _panBorder ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
        _tileView.move(-_panSpeed, 0);
    } else if ((pixelPos.y >= _window->getSize().y*.25 && pixelPos.y < _window->getSize().y*.25 + _panBorder ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Up))) {
        _tileView.move(0, -_panSpeed);
    } else if ((pixelPos.y > _window->getSize().y - _panBorder && pixelPos.y <= _window->getSize().y ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::Down))) {
        _tileView.move(0, _panSpeed);
    }
}

void TileMapEditor::updateUIView(sf::Event event) {
    _window->setView(_uiView);

    _gridSettingsStack->update(event);
}

void TileMapEditor::drawTileView() {
    _window->setView(_tileView);

    for (int r = 0; r < _rows; r++) {
        for (int c = 0; c < _columns; c++) {
            _window->draw(*_tiles[r][c]);
        }
    }
}

void TileMapEditor::drawUIView() {
    _window->setView(_uiView);

    _window->draw(*_gridSettingsStack);
}

