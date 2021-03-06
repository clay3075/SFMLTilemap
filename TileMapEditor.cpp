//
// Created by Clay Reddick on 2/7/21.
//

#include <iostream>
#include "TileMapEditor.h"
#include "UI/Label.h"
#include "UI/UIStack.h"

TileMapEditor::TileMapEditor(sf::RenderWindow *window, std::string filePath)  {
    _window = window;
    _tileView.zoom(_zoom);
    _tileView.setViewport(sf::FloatRect(0.0f, .25f, 1, 1));
    _window->setView(_tileView);

    _uiView.zoom(1);
    _uiView.setViewport(sf::FloatRect(0, 0, 1, 1));

    initMap(filePath);
    _selectedTexture = mapInfo->getTexture(mapInfo->getTextureIds().front());
    auto _dimensionStack = new UI::UIStack(Horizontal);
    _dimensionStack->setPadding(10);
    _widthInput =new UI::TextInput(_window, UI::Dimensions(120, 50));
    _widthInput->setTextAlignment(UI::Alignment::Center);
    _widthInput->setText(std::to_string(mapInfo->getDimensions().width));
    _heightInput = new UI::TextInput(_window, UI::Dimensions(120, 50));
    _heightInput->setTextAlignment(UI::Alignment::Center);
    _heightInput->setText(std::to_string(mapInfo->getDimensions().height));
    auto _xLabel = new UI::Label(_window, UI::Dimensions(30, 50));
    _xLabel->setBackgroundColor(sf::Color::Transparent);
    _xLabel->setTextColor(sf::Color::White);
    _xLabel->setText("X");
    _dimensionStack->insert(_widthInput);
    _dimensionStack->insert(_xLabel);
    _dimensionStack->insert(_heightInput);

    auto _gridDimLabelStack = new UI::UIStack(Horizontal);
    _gridDimLabelStack->setPadding(50);
    auto _rowLabel = new UI::Label(_window, UI::Dimensions(120, 50));
    _rowLabel->setBackgroundColor(sf::Color::Transparent);
    _rowLabel->setTextColor(sf::Color::White);
    _rowLabel->setText("Rows");
    auto _columnLabel = new UI::Label(_window, UI::Dimensions(120, 50));
    _columnLabel->setBackgroundColor(sf::Color::Transparent);
    _columnLabel->setTextColor(sf::Color::White);
    _columnLabel->setText("Cols");
    _gridDimLabelStack->insert(_rowLabel);
    _gridDimLabelStack->insert(_columnLabel);

    auto _gridDimInputStack = new UI::UIStack(Horizontal);
    _gridDimInputStack->setPadding(50);
    _rowInput = new UI::TextInput(_window, UI::Dimensions(120, 50));
    _rowInput->setTextAlignment(UI::Alignment::Center);
    _rowInput->setText(std::to_string(mapInfo->getMap().size()));
    _colInput = new UI::TextInput(_window, UI::Dimensions(120, 50));
    _colInput->setTextAlignment(UI::Alignment::Center);
    _colInput->setText(std::to_string(mapInfo->getMap().size() > 0 ? mapInfo->getMap()[0].size() : 0));
    _gridDimInputStack->insert(_rowInput);
    _gridDimInputStack->insert(_colInput);

    auto _gridSettingsButtonStack = new UI::UIStack(Horizontal);
    _gridSettingsButtonStack->setPadding(20);
    auto _updateButton = new UI::Button(_window, UI::Dimensions(150, 50));
    _updateButton->setText("Update");
    _updateButton->setOnClick([this] { updateGrid(); });
    auto _saveButton = new UI::Button(_window, UI::Dimensions(120, 50));
    _saveButton->setText("Save");
    _saveButton->setOnClick([this] { mapInfo->save(); });
    _gridSettingsButtonStack->insert(_updateButton);
    _gridSettingsButtonStack->insert(_saveButton);

    _gridSettingsStack = new UI::UIStack(Vertical, UI::Point(5, 5));
    _gridSettingsStack->setPadding(5);
    _gridSettingsStack->insert(_dimensionStack);
    _gridSettingsStack->insert(_gridDimLabelStack);
    _gridSettingsStack->insert(_gridDimInputStack);
    _gridSettingsStack->insert(_gridSettingsButtonStack);

    _tileOperationStack = new UI::UIStack(Vertical, UI::Point(_gridSettingsStack->getDimensions().width + _gridSettingsStack->getPosition().x, 5));
    _tileOperationStack->setPadding(5);
    auto _zoomLabel = new UI::Label(_window, UI::Dimensions(90, 40));
    _zoomLabel->setTextAlignment(UI::Alignment::Center);
    _zoomLabel->setText("Zoom");
    auto _zoomStack = new UI::UIStack(Horizontal);
    _zoomStack->setPadding(10);
    auto _zoomOutButton = new UI::Button(_window, UI::Dimensions(50, 50));
    _zoomOutButton->setTextAlignment(UI::Alignment::Center);
    _zoomOutButton->setText("-");
    _zoomOutButton->setOnClick([this] { this->_zoom += .1; this->_tileView.zoom(_zoom); });
    auto _zoomInButton = new UI::Button(_window, UI::Dimensions(50, 50));
    _zoomInButton->setText("+");
    _zoomInButton->setTextAlignment(UI::Alignment::Center);
    _zoomInButton->setOnClick([this] { this->_zoom -= .1; this->_tileView.zoom(_zoom); });
    _zoomStack->insert(_zoomOutButton);
    _zoomStack->insert(_zoomInButton);
    auto _textureContainer = new UI::TextureContainer(_window);
    _textureContainer->setMaxHorizontalTextureCount(9);
    _tileOperationStack->insert(_zoomLabel);
    _tileOperationStack->insert(_zoomStack);
    _tileOperationStack->insert(_textureContainer);
    auto onTextureSelected = [this](sf::Texture* selectedTexture) {
        _selectedTexture = selectedTexture;
    };
    for (auto texture : mapInfo->getTextures()) {
        _textureContainer->addTexture(texture.second, onTextureSelected);
    }
    _textureContainer->setOnNewImageAdded([this, _textureContainer, onTextureSelected](std::string path){
        auto texture = mapInfo->addTexture(path);
        if (texture)
            _textureContainer->addTexture(texture, onTextureSelected);
    });
}

void TileMapEditor::initMap() {
    for (int r = 0; r < mapInfo->getMap().size(); r++) {
        _tiles.emplace_back();
        for (int c = 0; c < mapInfo->getMap()[r].size(); c++) {
            auto point = UI::Point(c, r);
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

    delete _gridSettingsStack;
    delete _tileOperationStack;

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
        clearMap();
        mapInfo->resetMap(std::stoi(_rowInput->getText()), std::stoi(_colInput->getText()));
        mapInfo->setDimensions(UI::Dimensions(std::stoi(_widthInput->getText()), std::stoi(_heightInput->getText())));
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

void TileMapEditor::update() {
    _gridSettingsStack->update();
    _tileOperationStack->update();
}

