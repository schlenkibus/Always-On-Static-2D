#pragma once
#include <SFML/Graphics.hpp>
#include <functional>
#include "Label.h"

class Button {
public:
    Button(std::function<void(void)> callback, std::string text, sf::Texture& texture, sf::Vector2f pos);
    void update(double deltaTime);
    void draw(sf::RenderWindow& window);
private:
    std::function<void(void)> m_callback;
    bool isClicked();
    bool isHovered();
    sf::Sprite m_sprite;
    Label m_label;
	sf::Color hover;
	sf::Color normal;
};