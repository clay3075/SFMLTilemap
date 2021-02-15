//
// Created by Clay Reddick on 2/7/21.
//

#ifndef SFMLTILEMAP_TILEMAPEDITOR_H
#define SFMLTILEMAP_TILEMAPEDITOR_H
#include <SFML/Graphics.hpp>
#include "UI/Dimensions.h"
#include "UI/Point.h"
#include "BuilderTile.h"
#include "UI/TextInput.h"
#include "UI/UIStack.h"
#include "UI/Label.h"
#include "UI/Button.h"
#include "TileMapFileInfo.h"
#include "UI/TextureContainer.h"
#include <vector>
#include <map>
#include <memory>

class TileMapEditor {
public:
    explicit TileMapEditor(sf::RenderWindow* window, std::string filePath);
    void draw();
    void update(sf::Event event);
    void update();
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
    UI::TextInput* _widthInput = nullptr;
    UI::TextInput* _heightInput = nullptr;
    UI::TextInput* _rowInput = nullptr;
    UI::TextInput* _colInput = nullptr;

    // frees all children
    UI::UIStack* _gridSettingsStack = nullptr;
    UI::UIStack* _tileOperationStack = nullptr;

    void updateTileView(sf::Event event);
    void updateUIView(sf::Event event);
    void drawTileView();
    void drawUIView();
    void updateGrid();
    void textureChanged(BuilderTile* tile, sf::Texture* texture);
};


#endif //SFMLTILEMAP_TILEMAPEDITOR_H
