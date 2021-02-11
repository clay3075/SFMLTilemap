//
// Created by Clay Reddick on 2/7/21.
//

#ifndef SFMLTILEMAP_TILEMAPEDITOR_H
#define SFMLTILEMAP_TILEMAPEDITOR_H
#include <SFML/Graphics.hpp>
#include "Dimensions.h"
#include "Point.h"
#include "BuilderTile.h"
#include "TextInput.h"
#include "UIStack.h"
#include "Label.h"
#include "Button.h"
#include <vector>
#include <map>
#include <memory>

class TileMapEditor {
public:
    explicit TileMapEditor(sf::RenderWindow* window);
    void setTileDimensions(Dimensions tileDim) { _tileDimensions = tileDim; }
    void draw();
    void update(sf::Event event);
    void initMap();
    void clearMap();
    void clearTextures();
    ~TileMapEditor();
private:
    sf::RenderWindow* _window;
    sf::View _uiView;
    sf::View _tileView;
    Dimensions _tileDimensions = Dimensions(64, 64);
    int _rows = 16;
    int _columns = 16;
    std::vector<std::vector<BuilderTile*>> _tiles;
    std::map<int, sf::Texture*> _textures;
    sf::Texture* _selectedTexture = nullptr;
    float _panSpeed = 5;
    float _panBorder = 50;

    UIStack* _dimensionStack = nullptr;
    TextInput* _widthInput = nullptr;
    TextInput* _heightInput = nullptr;
    Label* _xLabel = nullptr;

    UIStack* _gridDimLabelStack = nullptr;
    Label* _rowLabel = nullptr;
    Label* _columnLabel = nullptr;

    UIStack* _gridDimInputStack = nullptr;
    TextInput* _rowInput = nullptr;
    TextInput* _colInput = nullptr;

    Button* _updateButton = nullptr;

    UIStack* _gridSettingsStack = nullptr;

    void updateTileView(sf::Event event);
    void updateUIView(sf::Event event);
    void drawTileView();
    void drawUIView();
};


#endif //SFMLTILEMAP_TILEMAPEDITOR_H
