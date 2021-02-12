//
// Created by Clay Reddick on 1/26/21.
//

#include "TileMap.h"
#include "TileMapFileInfo.h"
#include <iostream>
#include <fstream>
#include <math.h>

TileMap::TileMap(std::string tileMapFilePath) {
    this->_tileMapFilePath = tileMapFilePath;
    this->initGrid(tileMapFilePath);
}

void TileMap::printGrid() {
    std::cout << this->tileDimensions.width << "x" << this->tileDimensions.height << std::endl;
    Tile* tmpTile;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            tmpTile = grid[i][j];
            std::cout << "{" << tmpTile->getType() << "," << tmpTile->getCollision() << "} ";
        }
        std::cout << std::endl;
    }
}

void TileMap::initGrid(std::string path) {
    auto mapInfo = TileMapFileInfo::loadMapFromFile(path);
    tileDimensions = mapInfo.getDimensions();
    texturePaths = mapInfo.getTexturePaths();
    textureCollisions = mapInfo.getTextureCollisions();

    grid.emplace_back();
    int rowCount = 0;
    int colCount;
    for (auto row : mapInfo.getMap()) {
        colCount = 0;
        for (int textureId : row) {
            auto tmpTile = new Tile();
            tmpTile->setType(textureId);
            tmpTile->setTexturePath(texturePaths[tmpTile->getType()]);
            tmpTile->setCollision(textureCollisions[tmpTile->getType()]);
            tmpTile->setPosition(Point(colCount, rowCount));
            tmpTile->setDimensions(getTileDimension());
            this->grid[rowCount].push_back(tmpTile);
            grid[rowCount].push_back(tmpTile);
            colCount++;
        }
        grid.emplace_back();
        rowCount++;
    }
}

Tile* TileMap::checkForCollision(float x, float y) {
    x = ceil(x/this->tileDimensions.width) - 1;
    y = ceil(y/this->tileDimensions.height) - 1;

    if (y >= this->grid.size() || x >= this->grid[y].size() || y < 0 || x < 0)
        return NULL;

    Tile* tile = this->grid[y][x];

    return tile->getCollision() ? tile : NULL;
}

Tile* TileMap::checkForCollision(float left, float top, float width, float height, float boxBuffer) {
    float xCenter = left + width/2;
    float yCenter = top + height/2;

    Tile* collisions [4] = {checkForCollision(xCenter, top+boxBuffer), checkForCollision(xCenter, top + height - boxBuffer),
                            checkForCollision(left + boxBuffer, yCenter), checkForCollision(left + width - boxBuffer, yCenter)};

    for (auto tile : collisions) {
        if (tile)
            return tile;
    }

    return NULL;
}

void TileMap::reset() {
    for (auto row : this->grid) {
        row.clear();
    }
    this->grid.clear();
    this->initGrid(this->_tileMapFilePath);
}

