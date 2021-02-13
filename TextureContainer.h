//
// Created by Clay Reddick on 2/13/21.
//

#ifndef SFMLTILEMAP_TEXTURECONTAINER_H
#define SFMLTILEMAP_TEXTURECONTAINER_H
#include "UIStack.h"
#include <SFML/Graphics.hpp>


class TextureContainer : public UIStack {
public:
    TextureContainer(sf::RenderWindow* window, const Point &position = Point()) : UIStack(Horizontal, position) {
        _window = window;
        setPadding(5);
    }
    void addTexture(sf::Texture* texture, std::function<void(sf::Texture*)> onSelected);
private:
    sf::RenderWindow* _window;
};


#endif //SFMLTILEMAP_TEXTURECONTAINER_H
