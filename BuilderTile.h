//
// Created by Clay Reddick on 2/7/21.
//

#ifndef SFMLTILEMAP_BUILDERTILE_H
#define SFMLTILEMAP_BUILDERTILE_H
#include <SFML/Graphics.hpp>
#include "UI/Point.h"
#include "UI/Dimensions.h"

class BuilderTile : public sf::Drawable {
public:
    explicit BuilderTile(UI::Dimensions dim, UI::Point point) {
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
    void setOnTextureChanged(std::function<void(BuilderTile*, sf::Texture*)> onTextureChanged) { _onTextureChanged = onTextureChanged; }
    UI::Point getPosition() { return _point; }
private:
    bool _collision = false;
    bool _textureChanged = false;
    bool _mouseCaptured = false;
    sf::RectangleShape _sprite;
    UI::Dimensions _dimensions;
    UI::Point _point;
    sf::Texture* _oldTexture = nullptr;
    sf::Texture* _currentTexture = nullptr;
    std::function<void(BuilderTile*, sf::Texture*)> _onTextureChanged = nullptr;
};


#endif //SFMLTILEMAP_BUILDERTILE_H
