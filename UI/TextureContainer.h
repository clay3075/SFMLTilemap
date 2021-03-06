//
// Created by Clay Reddick on 2/13/21.
//

#ifndef SFMLTILEMAP_TEXTURECONTAINER_H
#define SFMLTILEMAP_TEXTURECONTAINER_H
#include "UIStack.h"
#include "Button.h"
#include "ImageSelector.h"
#include "Point.h"
#include <SFML/Graphics.hpp>


namespace UI {
    class TextureContainer : public UIStack {
    public:
        TextureContainer(sf::RenderWindow* window, const Point &position = Point());
        ~TextureContainer() override;
        void addTexture(sf::Texture* texture, std::function<void(sf::Texture*)> onSelected);
        void addButton(Button* button);
        void removeButton(Button* button);
        void setMaxHorizontalTextureCount(int count) { _maxHorizontalTextureCount = count; }
        void update() override;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setOnNewImageAdded(std::function<void(std::string texturePath)> onNewImageAdded) { _onNewImageAdded = onNewImageAdded; }
    private:
        sf::RenderWindow* _window;
        ImageSelector* addTextureWindow;
        int _maxHorizontalTextureCount = 5;
        Button* _addTextureButton = nullptr;
        std::function<void(std::string texturePath)> _onNewImageAdded = nullptr;
    };
}


#endif //SFMLTILEMAP_TEXTURECONTAINER_H
