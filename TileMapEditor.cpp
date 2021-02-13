//
// Created by Clay Reddick on 2/7/21.
//

#include <iostream>
#include "TileMapEditor.h"
#include "Label.h"
#include "UIStack.h"

TileMapEditor::TileMapEditor(sf::RenderWindow *window, std::string filePath)  {
    _window = window;
    _tileView.zoom(_zoom);
    _tileView.setViewport(sf::FloatRect(0.0f, .25f, 1, 1));
    _window->setView(_tileView);

    _uiView.zoom(1);
    _uiView.setViewport(sf::FloatRect(0, 0, 1, 1));

    initMap(filePath);
    _selectedTexture = mapInfo->getTexture(mapInfo->getTextureIds().front());

    _dimensionStack = new UIStack(Horizontal);
    _dimensionStack->setPadding(10);
    _widthInput =new TextInput(_window, Dimensions(120, 50));
    _widthInput->setText(std::to_string(mapInfo->getDimensions().width));
    _heightInput = new TextInput(_window, Dimensions(120, 50));
    _heightInput->setText(std::to_string(mapInfo->getDimensions().height));
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
    _rowInput->setText(std::to_string(mapInfo->getMap().size()));
    _colInput = new TextInput(_window, Dimensions(120, 50));
    _colInput->setText(std::to_string(mapInfo->getMap().size() > 0 ? mapInfo->getMap()[0].size() : 0));
    _gridDimInputStack->insert(_rowInput);
    _gridDimInputStack->insert(_colInput);

    _gridSettingsButtonStack = new UIStack(Horizontal);
    _gridSettingsButtonStack->setPadding(10);
    _updateButton = new Button(_window, Dimensions(170, 50));
    _updateButton->setText("Update");
    _updateButton->setOnClick([this] { updateGrid(); });
    _saveButton = new Button(_window, Dimensions(120, 50));
    _saveButton->setText("Save");
    _saveButton->setOnClick([this] { mapInfo->save(); });
    _gridSettingsButtonStack->insert(_updateButton);
    _gridSettingsButtonStack->insert(_saveButton);

    _gridSettingsStack = new UIStack(Vertical, Point(5, 5));
    _gridSettingsStack->setPadding(5);
    _gridSettingsStack->insert(_dimensionStack);
    _gridSettingsStack->insert(_gridDimLabelStack);
    _gridSettingsStack->insert(_gridDimInputStack);
    _gridSettingsStack->insert(_gridSettingsButtonStack);

    _tileOperationStack = new UIStack(Vertical, Point(_gridSettingsStack->getDimensions().width + _gridSettingsStack->getPosition().x, 5));
    _tileOperationStack->setPadding(5);
    _zoomStack = new UIStack(Horizontal);
    _zoomStack->setPadding(10);
    _zoomOutButton = new Button(_window, Dimensions(50, 50));
    _zoomOutButton->setText("-");
    _zoomOutButton->setOnClick([this] { this->_zoom += .1; this->_tileView.zoom(_zoom); });
    _zoomInButton = new Button(_window, Dimensions(50, 50));
    _zoomInButton->setText("+");
    _zoomInButton->setOnClick([this] { this->_zoom -= .1; this->_tileView.zoom(_zoom); });
    _zoomStack->insert(_zoomOutButton);
    _zoomStack->insert(_zoomInButton);
    _textureContainer = new TextureContainer(_window);
    _textureContainer->setMaxHorizontalTextureCount(9);
    _tileOperationStack->insert(_zoomStack);
    _tileOperationStack->insert(_textureContainer);
    for (auto texture : mapInfo->getTextures()) {
        _textureContainer->addTexture(texture.second, [this](sf::Texture* selectedTexture) {
            _selectedTexture = selectedTexture;
        });
    }
}

void TileMapEditor::initMap() {
    for (int r = 0; r < mapInfo->getMap().size(); r++) {
        _tiles.emplace_back();
        for (int c = 0; c < mapInfo->getMap()[r].size(); c++) {
            auto point = Point(c, r);
            auto tile = new BuilderTile(mapInfo->getDimensions(), point);

            tile->setOnTextureChanged([this](BuilderTile* bT, sf::Texture* t) {
                textureChanged(bT, t);
            });
            if (std::find(mapInfo->getTextureIds().begin(), mapInfo->getTextureIds().end(), mapInfo->getMap()[r][c]) != mapInfo->getTextureIds().end())
                tile->setTexture(mapInfo->getTexture(mapInfo->getMap()[r][c]));

            _tiles[r].push_back(tile);
        }
    }
}

void TileMapEditor::initMap(std::string filePath) {
    mapInfo = TileMapFileInfo::loadMapFromFile(filePath);

    initMap();
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
    for (int r = 0; r < mapInfo->getMap().size(); r++) {
        for (int c = 0; c < mapInfo->getMap()[r].size(); c++) {
            delete _tiles[r][c];
        }
    }
    _tiles.clear();
}

TileMapEditor::~TileMapEditor() {
    clearMap();

//    delete _dimensionStack;
//    delete _widthInput;
//    delete _heightInput;
//    delete _xLabel;
//
//    delete _gridDimLabelStack;
//    delete _rowLabel;
//    delete _columnLabel;
//
//    delete _gridDimInputStack;
//    delete _rowInput;
//    delete _colInput;
//
//    delete _gridSettingsButtonStack;
//    delete _updateButton;
//    delete _saveButton;

    delete _gridSettingsStack;
    delete _tileOperationStack;
//    delete _zoomStack;
//    delete _zoomInButton;
//    delete _zoomOutButton;
//    delete _textureContainer;

    delete mapInfo;
}

void TileMapEditor::updateTileView(sf::Event event) {
    _window->setView(_tileView);

    for (int r = 0; r < mapInfo->getMap().size(); r++) {
        for (int c = 0; c < mapInfo->getMap()[r].size(); c++) {
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
    _tileOperationStack->update(event);
}

void TileMapEditor::drawTileView() {
    _window->setView(_tileView);

    for (int r = 0; r < mapInfo->getMap().size(); r++) {
        for (int c = 0; c < mapInfo->getMap()[r].size(); c++) {
            _window->draw(*_tiles[r][c]);
        }
    }
}

void TileMapEditor::drawUIView() {
    _window->setView(_uiView);

    _window->draw(*_gridSettingsStack);
    _window->draw(*_tileOperationStack);
}

void TileMapEditor::updateGrid() {
    try {
        mapInfo->resetMap(std::stoi(_rowInput->getText()), std::stoi(_colInput->getText()));
        mapInfo->setDimensions(Dimensions(std::stoi(_widthInput->getText()), std::stoi(_heightInput->getText())));
        clearMap();
        initMap();
    } catch (std::exception ex) {
        //TODO: Tell user
    }

}

void TileMapEditor::textureChanged(BuilderTile *tile, sf::Texture *texture) {
    int id = -1;
    for (auto tmpTexture : mapInfo->getTextures()) {
        if (texture == tmpTexture.second) {
            id = tmpTexture.first;
        }
    }
    int r = tile->getPosition().y;
    int c = tile->getPosition().x;
    mapInfo->getMap()[r][c] = id;
}

