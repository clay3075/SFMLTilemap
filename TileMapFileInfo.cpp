//
// Created by Clay Reddick on 2/12/21.
//

#include "TileMapFileInfo.h"
#include <fstream>

TileMapFileInfo* TileMapFileInfo::loadMapFromFile(std::string filePath) {
    TileMapFileInfo* mapInfo = new TileMapFileInfo();
    int posX = 0;
    int posY = 0;
    std::string tmpInput;

    std::ifstream stream;
    stream.open(filePath);

    if (stream.is_open()) {
        std::getline(stream, tmpInput);
        int delim = tmpInput.find('x');
        mapInfo->_tileDimensions.width = std::stoi(tmpInput.substr(0, delim));
        mapInfo->_tileDimensions.height = std::stoi(tmpInput.substr(delim+1, tmpInput.size()));

        while (std::getline(stream, tmpInput) && tmpInput[0] == '*') {
            int pos, pos2;
            pos = tmpInput.find(";");
            pos2 = tmpInput.find(";", pos+1);
            int id = std::stoi(tmpInput.substr(1, pos));
            mapInfo->_texturePaths.insert(std::pair<int, std::string>(id, tmpInput.substr(pos+1, pos2-pos-1)));
            auto tmpTexture = new sf::Texture();
            if (!tmpTexture->loadFromFile(mapInfo->_texturePaths[id])) {
                std:: cout << "Error loading texture.";
            }
            mapInfo->_textures.insert(std::pair<int, sf::Texture*>(id, tmpTexture));
            mapInfo->_textureCollisions.insert(std::pair<int, bool>(id, std::stoi(tmpInput.substr(pos2+1))));
        }


        do {
            mapInfo->_map.emplace_back();
            int pos;
            tmpInput += " ";
            posX = 0;
            while((pos = tmpInput.find(" ")) != std::string::npos) {
                mapInfo->_map[posY].push_back(std::stoi(tmpInput.substr(0, pos)));
                tmpInput.erase(0, pos + 1);
                posX++;
            }

            posY++;
        } while (std::getline(stream, tmpInput));

        stream.close();
    }

    return mapInfo;
}

TileMapFileInfo::~TileMapFileInfo() {
    for (auto textureInfo : _textures) {
        delete textureInfo.second;
    }
    _textures.clear();
}

void TileMapFileInfo::resetMap(int rows, int cols) {
    _map.resize(rows, std::vector<int, std::allocator<int>>());

    for (auto row : _map) {
        row.resize(cols, 0);
    }
}

