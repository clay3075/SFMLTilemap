//
// Created by Clay Reddick on 2/7/21.
//

#ifndef SFMLTILEMAP_BUILDERTILE_H
#define SFMLTILEMAP_BUILDERTILE_H
#include <SFML/Graphics.hpp>
#include "Point.h"
#include "Dimensions.h"

class BuilderTile : public sf::Drawable {
public:
    explicit BuilderTile(Dimensions dim, Point point) {
        _dimensions = dim;
        _point = point;
        _sprite.setFillColor(sf::Color::Black);
    }
    void setCollision(bool collision);
    void setTexture(sf::Texture* texture);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void mouseEnter(sf::Texture* texture);
    void mouseExit();
    void update(sf::RenderWindow* window, sf::Texture* texture);
private:
    bool _collision = false;
    bool _textureChanged = false;
    bool _mouseCaptured = false;
    sf::RectangleShape _sprite;
    Dimensions _dimensions;
    Point _point;
    sf::Texture* _tmpTexture = nullptr;
    sf::Texture* _currentTexture = nullptr;
};


#endif //SFMLTILEMAP_BUILDERTILE_H
