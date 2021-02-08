//
// Created by Clay Reddick on 1/26/21.
//

#ifndef SFMLTILEMAP_DIMENSIONS_H
#define SFMLTILEMAP_DIMENSIONS_H


class Dimensions {
public:
    Dimensions() = default;
    Dimensions(int width, int height) {
        this->width = width;
        this->height = height;
    }
    int width;
    int height;
};


#endif //SFMLTILEMAP_DIMENSIONS_H
