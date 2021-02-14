//
// Created by Clay Reddick on 2/13/21.
//

#ifndef SFMLTILEMAP_IMAGESELECTOR_H
#define SFMLTILEMAP_IMAGESELECTOR_H
#include <SFML/Graphics.hpp>
#include "UIStack.h"
#include "TextInput.h"
#include <filesystem>

class ImageSelector : public sf::RenderWindow {
public:
    explicit ImageSelector(const sf::VideoMode &mode);
    ~ImageSelector() override;
    void show() { setVisible(true); setActive(true); }
    void hide() { setVisible(false); setActive(false); }
    void update();
    void draw();
    void setOnImageSelected(std::function<void(std::string texturePath)> onImageSelected) { _onImageSelected = onImageSelected; }
private:
    UIStack* _imageList = nullptr;
    //get freed by _imageList
    TextInput* _pathInput = nullptr;
    std::vector<std::string> _imgExtensions {".jpg", ".png"};
    std::function<void(std::string texturePath)> _onImageSelected = nullptr;
    bool _loading = false;

    void loadImages();
    bool buttonExistsForPath(std::string path);
    void clearButtons();
};


#endif //SFMLTILEMAP_IMAGESELECTOR_H
