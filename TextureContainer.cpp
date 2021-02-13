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
    if (texture) {
        button->setBackgroundTexture(*texture);
    }

    bool inserted = false;
    for (auto element : getUIElements()) {
        auto container = (UIStack*)element;
        if (container->getUIElements().size() < _maxHorizontalTextureCount) {
            container->insert(button);
            inserted = true;
            break;
        }
    }

    if (!inserted) {
        auto newStack = new UIStack(Horizontal);
        newStack->setPadding(5);
        newStack->insert(button);
        insert(newStack);
    }
}
