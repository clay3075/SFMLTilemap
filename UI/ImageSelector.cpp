//
// Created by Clay Reddick on 2/13/21.
//

#include "ImageSelector.h"
#include "Button.h"
#include "Dimensions.h"
#include "Point.h"
#include "TextInput.h"
#include "UIStack.h"

namespace fs = std::filesystem;

UI::ImageSelector::ImageSelector(const sf::VideoMode &mode) : RenderWindow(mode, "Image Selector") {
    _imageList = new UIStack(Vertical, Point(5, 5));
    _imageList->setPadding(5);
    _pathInput = new TextInput(this, UI::Dimensions(this->getSize().x - 10, 50));
    _pathInput->setIsEditable(true);
    _pathInput->setText("..");
    _imageList->insert(_pathInput);
    loadImages();
}

void UI::ImageSelector::update() {
    sf::Event event;

    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            hide();
        if (event.type == sf::Event::KeyReleased)
            _loading = false;

        _imageList->update(event);
    }

    if (!_loading && sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        _loading = true;
        loadImages();
    }
    _imageList->update();
}

void UI::ImageSelector::draw() {
    clear();
    _imageList->draw(*this, sf::RenderStates());
    display();
}

UI::ImageSelector::~ImageSelector() {
    sf::RenderWindow::~RenderWindow();

    delete _imageList;
}

void UI::ImageSelector::loadImages() {
    try {
        clearButtons();
        std::vector<std::string> paths;
        for(auto& p: fs::directory_iterator(_pathInput->getText())) {
            if (std::find(_imgExtensions.begin(), _imgExtensions.end(), p.path().extension().string()) != _imgExtensions.end())
                paths.push_back(p.path().string());
        }

        for(auto path : paths) {
            if (buttonExistsForPath(path)) continue;

            auto button = new UI::Button(this, UI::Dimensions(getSize().x - 10, 50));
            button->setText(path);
            button->setOnClick([path,this](){
                if (_onImageSelected) _onImageSelected(path);
            });
            _imageList->insert(button);
        }
    } catch (std::exception ex) {

    }
}

bool UI::ImageSelector::buttonExistsForPath(std::string path) {
    bool exists = false;
    if (_imageList->getUIElements().size() > 1) {
        for (auto iter = _imageList->getUIElements().begin() + 1; iter != _imageList->getUIElements().end(); iter++) {
            auto button = (UI::Button *) *iter;
            if (button->getText() == path) {
                exists = true;
                break;
            }
        }
    }

    return exists;
}

void UI::ImageSelector::clearButtons() {

    if (_imageList->getUIElements().size() > 1) {
        for (auto iter = _imageList->getUIElements().begin() + 1; iter != _imageList->getUIElements().end(); iter++) {
            _imageList->remove(*iter);
        }
    }
}
