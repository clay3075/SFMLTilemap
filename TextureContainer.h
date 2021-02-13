//
// Created by Clay Reddick on 2/13/21.
//

#ifndef SFMLTILEMAP_TEXTURECONTAINER_H
#define SFMLTILEMAP_TEXTURECONTAINER_H
#include "UIStack.h"
#include <SFML/Graphics.hpp>


class TextureContainer : public UIStack {
public:
    TextureContainer(sf::RenderWindow* window, const Point &position = Point()) : UIStack(Vertical, position) {
        _window = window;
        setPadding(5);
    }
    void addTexture(sf::Texture* texture, std::function<void(sf::Texture*)> onSelected);
    void setMaxHorizontalTextureCount(int count) { _maxHorizontalTextureCount = count; }
private:
    sf::RenderWindow* _window;
    int _maxHorizontalTextureCount = 5;
};


#endif //SFMLTILEMAP_TEXTURECONTAINER_H
