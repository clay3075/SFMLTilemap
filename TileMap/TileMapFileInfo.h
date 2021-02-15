//
// Created by Clay Reddick on 2/12/21.
//

#ifndef SFMLTILEMAP_TILEMAPFILEINFO_H
#define SFMLTILEMAP_TILEMAPFILEINFO_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../UI/Dimensions.h"

class TileMapFileInfo {
public:
    std::string getTexturePath(const int type) { return _texturePaths.at(type); }
    std::vector<std::vector<int>>& getMap() { return _map; }
    static TileMapFileInfo* loadMapFromFile(std::string filePath);
    bool save();
    UI::Dimensions getDimensions() { return _tileDimensions; }
    void setDimensions(UI::Dimensions dim) { _tileDimensions = dim; }
    std::map<int, std::string> getTexturePaths() { return _texturePaths; }
    sf::Texture* getTexture(const int id) { return _textures[id]; }
    sf::Texture* addTexture(std::string texturePath);
    std::vector<int> getTextureIds() {
        std::vector<int> ids;
        for (auto texture : _texturePaths) {
            ids.push_back(texture.first);
        }

        return ids;
    }
    std::map<int, sf::Texture*> getTextures() { return _textures; }
    std::map<int, bool> getTextureCollisions() { return  _textureCollisions; }
    std::string getFilePath() { return _tileMapFilePath; }
    void resetMap(int rows = 0, int cols = 0);
    ~TileMapFileInfo();
private:
    std::vector<std::vector<int>> _map;
    std::map<int, sf::Texture*> _textures;
    std::map<int, std::string> _texturePaths;
    std::map<int, bool> _textureCollisions;
    std::string _tileMapFilePath;
    UI::Dimensions _tileDimensions{};
};

#endif //SFMLTILEMAP_TILEMAPFILEINFO_H
