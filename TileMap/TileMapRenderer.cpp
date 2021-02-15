//
// Created by Clay Reddick on 1/26/21.
//

#include "TileMapRenderer.h"

void TileMapRenderer::draw() {
    TileRenderer tmp;

    for (const auto& row : _tileMap.gridData()) {
        for (Tile* tile : row) {
            tmp = TileRenderer(_window, *tile);
            tmp.draw();
        }
    }
}
