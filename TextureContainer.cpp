//
// Created by Clay Reddick on 2/13/21.
//

#include "TextureContainer.h"
#include "Button.h"

void TextureContainer::addTexture(sf::Texture *texture, std::function<void(sf::Texture *)> onSelected) {
    auto button = new Button(_window, Dimensions(64, 64));
    button->setOnClick([texture, onSelected]() {
        onSelected(texture);
    });
    if (texture)
        button->setBackgroundTexture(*texture);
    insert(button);
}
