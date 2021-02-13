//
// Created by Clay Reddick on 2/13/21.
//

#include "ImageSelector.h"

ImageSelector::ImageSelector(const sf::VideoMode &mode) : RenderWindow(mode, "Image Selector") {

}

void ImageSelector::update() {
    sf::Event event;

    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            hide();
    }
}
