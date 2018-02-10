#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <functional>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class tvGameObject {
public:
    tvGameObject(sf::Texture& tex, sf::Vector2f pos, std::function<void(void)> callback);
    void update(double delta);
    void draw(sf::RenderWindow& window);
    sf::Sprite& getSprite();
protected:
    std::function<void(void)> m_callBack;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};