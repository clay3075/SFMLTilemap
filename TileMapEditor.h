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
#include "TextureContainer.h"
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

    // These get freed in the stack ui
    TextInput* _widthInput = nullptr;
    TextInput* _heightInput = nullptr;
    TextInput* _rowInput = nullptr;
    TextInput* _colInput = nullptr;

    // frees all children
    UIStack* _gridSettingsStack = nullptr;
    UIStack* _tileOperationStack = nullptr;

    void updateTileView(sf::Event event);
    void updateUIView(sf::Event event);
    void drawTileView();
    void drawUIView();
    void updateGrid();
    void textureChanged(BuilderTile* tile, sf::Texture* texture);
};


#endif //SFMLTILEMAP_TILEMAPEDITOR_H
