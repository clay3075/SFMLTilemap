//
// Created by Clay Reddick on 2/13/21.
//

#include "TextureContainer.h"
#include "Button.h"
#include "Alignment.h"
#include "Dimensions.h"
#include "ImageSelector.h"
#include "Point.h"
#include "UIStack.h"

UI::TextureContainer::TextureContainer(sf::RenderWindow *window, const UI::Point &position) : UIStack(UIStackDirection::Vertical, position) {
    _window = window;
    _addTextureButton = new UI::Button(window, UI::Dimensions(64, 64));
    _addTextureButton->setTextAlignment(UI::Alignment::Center);
    _addTextureButton->setText("+");
    _addTextureButton->setOnClick([this]() {
        addTextureWindow->setPosition(sf::Vector2i(0,0));
        addTextureWindow->show();
    });
    setPadding(5);
    addTextureWindow = new UI::ImageSelector(sf::VideoMode(1200, 800));
    addTextureWindow->setOnImageSelected([this](std::string path){
        if (_onNewImageAdded) _onNewImageAdded(path);
        addTextureWindow->hide();
    });
    _window->setActive(true);
    _window->requestFocus();
    addTextureWindow->hide();
}

void UI::TextureContainer::addTexture(sf::Texture *texture, std::function<void(sf::Texture *)> onSelected) {
    auto button = new UI::Button(_window, UI::Dimensions(64, 64));
    button->setOnClick([texture, onSelected]() {
        onSelected(texture);
    });
    if (texture) {
        button->setBackgroundTexture(*texture);
    }

    removeButton(_addTextureButton);
    addButton(button);
    addButton(_addTextureButton);
}

void UI::TextureContainer::addButton(UI::Button *button) {
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
        auto newStack = new UIStack(UIStackDirection::Horizontal);
        newStack->setPadding(5);
        newStack->insert(button);
        insert(newStack);
    }
}

void UI::TextureContainer::removeButton(UI::Button *button) {
    for (auto element : getUIElements()) {
        auto container = (UIStack *) element;
        container->remove(button, false);
    }
}

void UI::TextureContainer::update() {
    UIStack::update();

    addTextureWindow->update();
}

UI::TextureContainer::~TextureContainer() {
    UIStack::~UIStack();

    addTextureWindow->close();
    delete addTextureWindow;
}

void UI::TextureContainer::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    UIStack::draw(target, states);

    addTextureWindow->setActive(true);
    addTextureWindow->draw();
    addTextureWindow->setActive(false);
}


