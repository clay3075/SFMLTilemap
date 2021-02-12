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
#include "TileMapFileInfo.h"
#include <vector>
#include <map>
#include <memory>

class TileMapEditor {
public:
    explicit TileMapEditor(sf::RenderWindow* window, std::string filePath);
    void draw();
    void update(sf::Event event);
    void initMap(std::string filePath);
    void initMap();
    void clearMap();
    ~TileMapEditor();
private:
    sf::RenderWindow* _window;
    sf::View _uiView;
    sf::View _tileView;
    std::vector<std::vector<BuilderTile*>> _tiles;
    sf::Texture* _selectedTexture = nullptr;
    float _panSpeed = 5;
    float _panBorder = 50;
    float _zoom = 1;
    TileMapFileInfo* mapInfo;

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

    Button<TileMapEditor>* _updateButton = nullptr;

    UIStack* _gridSettingsStack = nullptr;

    UIStack* _zoomStack = nullptr;
    Button<TileMapEditor>* _zoomOutButton = nullptr;
    Button<TileMapEditor>* _zoomInButton = nullptr;

    void updateTileView(sf::Event event);
    void updateUIView(sf::Event event);
    void drawTileView();
    void drawUIView();
    void updateGrid();
};


#endif //SFMLTILEMAP_TILEMAPEDITOR_H
