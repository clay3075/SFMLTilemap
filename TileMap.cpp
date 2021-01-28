//
// Created by Clay Reddick on 1/26/21.
//

#include "TileMap.h"
#include <iostream>
#include <fstream>
#include <math.h>

const int ASCIIZERO = 48;

TileMap::TileMap(std::string tileMapFilePath) {
    this->initGrid(tileMapFilePath);
}

void TileMap::printGrid() {
    std::cout << this->tileDimensions.width << "x" << this->tileDimensions.height << std::endl;
    Tile tmpTile;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            tmpTile = grid[i][j];
            std::cout << "{" << tmpTile.getType() << "," << tmpTile.getCollision() << "} ";
        }
        std::cout << std::endl;
    }
}

void TileMap::initGrid(std::string path) {
    int posX;
    int posY;
    Tile tmpTile;
    std::string tmpInput;

    std::ifstream stream;
    stream.open(path);

    if (stream.is_open()) {
        std::getline(stream, tmpInput);
        int delim = tmpInput.find('x');
        this->tileDimensions.width = std::stoi(tmpInput.substr(0, delim));
        this->tileDimensions.height = std::stoi(tmpInput.substr(delim+1, tmpInput.size()));
        tmpTile.setDimensions(this->getTileDimension());

        this->grid.push_back(std::vector<Tile>());
        while (std::getline(stream, tmpInput) && tmpInput[0] == '*') {
            int pos, pos2;
            pos = tmpInput.find(";");
            pos2 = tmpInput.find(";", pos+1);
            int id = std::stoi(tmpInput.substr(1, pos));
            texturePaths.insert(std::pair<int, std::string>(id, tmpInput.substr(pos+1, pos2-pos-1)));
            textureCollisions.insert(std::pair<int, bool>(id, std::stoi(tmpInput.substr(pos2+1))));
        }

        do {
            int pos;
            tmpInput += " ";
            posX = 0;
            while((pos = tmpInput.find(" ")) != std::string::npos) {
                tmpTile.setType(std::stoi(tmpInput.substr(0, pos)));
                tmpTile.setTexturePath(texturePaths[tmpTile.getType()]);
                tmpTile.setCollision(textureCollisions[tmpTile.getType()]);
                tmpTile.setPosition(Point(posX, posY));
                this->grid[posY].push_back(tmpTile);
                tmpInput.erase(0, pos + 1);
                posX++;
            }

            posY++;
            this->grid.push_back(std::vector<Tile>());
        } while (std::getline(stream, tmpInput));

        stream.close();
    }
}

bool TileMap::checkForCollision(int x, int y) {
    x = round(x/this->tileDimensions.width);
    y = round(y/this->tileDimensions.height);

    if (x >= this->grid.size() || y >= this->grid[x].size())
        return true;

    return this->grid[x][y].getCollision();
}
