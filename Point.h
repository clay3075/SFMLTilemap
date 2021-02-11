//
// Created by Clay Reddick on 1/26/21.
//

#ifndef SFMLTILEMAP_POINT_H
#define SFMLTILEMAP_POINT_H

#include "Dimensions.h"

struct Point {
public:
    int x = 0;
    int y = 0;
    Point(int x, int y) { this->x = x; this->y = y; }
    Point() = default;
    Point &operator+=(const Point& Y) {
        this->x += Y.x;
        this->y += Y.y;
        return *this;
    }
    Point &operator+=(const Dimensions& Y) {
        this->x += Y.width;
        this->y += Y.height;
        return *this;
    }
};


#endif //SFMLTILEMAP_POINT_H
