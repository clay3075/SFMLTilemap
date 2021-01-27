//
// Created by Clay Reddick on 1/26/21.
//

#include "TileMap.h"
#include <iostream>
#include <fstream>

const int ASCIIZERO = 48;

TileMap::TileMap(std::string tileMapFilePath) {
    this->initGrid(tileMapFilePath);
}

void TileMap::printGrid() {
    std::cout << this->tileDimensions.width << "x" << this->tileDimensions.height << std::endl;
    for(int i = 0; i < grid.size(); i++) {
        for(int j = 0; j < grid[i].size(); j++) {
            std::cout << grid[i][j].getType() << " ";
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
            int pos;
            pos = tmpInput.find(";");
            texturePaths.insert(std::pair<int, std::string>(std::stoi(tmpInput.substr(1, pos)), tmpInput.substr(pos+1)));
        }

        do {
            int pos;
            tmpInput += " ";
            posX = 0;
            while((pos = tmpInput.find(" ")) != std::string::npos) {
                tmpTile.setType(std::stoi(tmpInput.substr(0, pos)));
                tmpTile.setTexturePath(texturePaths[tmpTile.getType()]);
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
