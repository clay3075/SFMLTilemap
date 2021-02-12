//
// Created by Clay Reddick on 2/12/21.
//

#ifndef SFMLTILEMAP_TILEMAPFILEINFO_H
#define SFMLTILEMAP_TILEMAPFILEINFO_H

class TileMapFileInfo {
public:
    std::string getTexturePath(const int type) { return _texturePaths.at(type); }
    std::vector<std::vector<int>>& getMap() { return _map; }
    static TileMapFileInfo loadMapFromFile(std::string filePath);
    Dimensions getDimensions() { return _tileDimensions; }
    std::map<int, std::string> getTexturePaths() { return _texturePaths; }
    std::map<int, bool> getTextureCollisions() { return  _textureCollisions; }
    std::string getFilePath() { return _tileMapFilePath; }
private:
    std::vector<std::vector<int>> _map;
    std::map<int, std::string> _texturePaths;
    std::map<int, bool> _textureCollisions;
    std::string _tileMapFilePath;
    Dimensions _tileDimensions{};
};

#endif //SFMLTILEMAP_TILEMAPFILEINFO_H
