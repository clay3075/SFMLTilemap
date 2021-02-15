//
// Created by Clay Reddick on 1/26/21.
//

#ifndef SFMLTILEMAP_TILE_H
#define SFMLTILEMAP_TILE_H
#include "UI/Point.h"
#include "UI/Dimensions.h"
#include <string>

class Tile {
public:
    UI::Point getPosition() { return this->position; };
    void setPosition(UI::Point pos) { this->position = pos; }
    UI::Dimensions getDimensions() { return this->dimensions; };
    void setDimensions(UI::Dimensions dim) { this->dimensions = dim; }
    inline int getType() { return this->type; }
    inline void setType(int type) { this->type = type; }
    std::string getTexturePath() { return texturePath; }
    void setTexturePath(std::string path) { texturePath = path; }
    bool getCollision() { return collision; }
    void setCollision(bool collision) { this->collision = collision; }
private:
    UI::Point position = UI::Point(0, 0);
    UI::Dimensions dimensions;
    int type = 0;
    std::string texturePath = "";
    bool collision = false;
};


#endif //SFMLTILEMAP_TILE_H
