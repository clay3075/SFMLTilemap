//
// Created by Clay Reddick on 2/13/21.
//

#ifndef SFMLTILEMAP_TEXTURECONTAINER_H
#define SFMLTILEMAP_TEXTURECONTAINER_H
#include "UIStack.h"
#include "Button.h"
#include "ImageSelector.h"
#include <SFML/Graphics.hpp>


class TextureContainer : public UIStack {
public:
    TextureContainer(sf::RenderWindow* window, const Point &position = Point()) : UIStack(Vertical, position) {
        _window = window;
        _addTextureButton = new Button(window, Dimensions(64, 64));
        _addTextureButton->setText("+");
        _addTextureButton->setOnClick([this]() {
            addTextureWindow->show();
        });
        setPadding(5);
        addTextureWindow = new ImageSelector(sf::VideoMode(400, 800));
        addTextureWindow->hide();
    }
    ~TextureContainer() override;
    void addTexture(sf::Texture* texture, std::function<void(sf::Texture*)> onSelected);
    void addButton(Button* button);
    void removeButton(Button* button);
    void setMaxHorizontalTextureCount(int count) { _maxHorizontalTextureCount = count; }
    void update() override;
private:
    sf::RenderWindow* _window;
    ImageSelector* addTextureWindow;
    int _maxHorizontalTextureCount = 5;
    Button* _addTextureButton;
};


#endif //SFMLTILEMAP_TEXTURECONTAINER_H
