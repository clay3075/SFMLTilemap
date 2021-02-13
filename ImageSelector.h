//
// Created by Clay Reddick on 2/13/21.
//

#ifndef SFMLTILEMAP_IMAGESELECTOR_H
#define SFMLTILEMAP_IMAGESELECTOR_H
#include <SFML/Graphics.hpp>

class ImageSelector : public sf::RenderWindow {
public:
    ImageSelector(const sf::VideoMode &mode);
    void show() { setVisible(true); }
    void hide() { setVisible(false); }
    void update();
private:
};


#endif //SFMLTILEMAP_IMAGESELECTOR_H
