//
// Created by Clay Reddick on 2/9/21.
//

#ifndef SFMLTILEMAP_TEXTINPUT_H
#define SFMLTILEMAP_TEXTINPUT_H
#include <string>
#include <SFML/Graphics.hpp>
#include "Dimensions.h"
#include "Point.h"
#include "UIElement.h"

class TextInput : public UIElement {
public:
    TextInput(sf::RenderWindow* window, Dimensions dim, Point position = Point());
    void update(sf::Event event) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setBorderThickness(const float width) {
        _shape.setOutlineThickness(width);
    }
    void setBorderColor(const sf::Color color) {
        _shape.setOutlineColor(color);
    }
    void setBackgroundColor(sf::Color color) {
        _shape.setFillColor(color);
    }
    void setTextColor(sf::Color color) {
        _sfText.setFillColor(color);
    }
    void setText(std::string text) {
        _text = text;
        resizeText();
    }
    void setIsEditable(bool editable) {
        _isEditable = editable;
    }
    void setFontSize(int size) {
        _sfText.setCharacterSize(size);
        resizeText();
    }
    void reposition() override;
protected:
    std::string _text;
    sf::RectangleShape _shape;
    sf::Text _sfText;
    bool _isEditable = true;

    void positionText();
    void resizeText();
};


#endif //SFMLTILEMAP_TEXTINPUT_H
