//
// Created by Clay Reddick on 2/7/21.
//

#ifndef SFMLTILEMAP_TILEMAPEDITOR_H
#define SFMLTILEMAP_TILEMAPEDITOR_H
#include <SFML/Graphics.hpp>
#include "Dimensions.h"
#include "Point.h"
#include "BuilderTile.h"
#include <vector>
#include <map>

class TileMapEditor {
public:
    explicit TileMapEditor(sf::RenderWindow* window);
//    void setTileDimensions(Dimensions tileDim) { _tileDimensions = tileDim; }
    void draw();
    void update();
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
};


#endif //SFMLTILEMAP_TILEMAPEDITOR_H
