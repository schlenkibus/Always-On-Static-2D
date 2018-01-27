#pragma once
#include <SFML/Graphics.hpp>

class IngameState;

class gameObject {
public:
    gameObject(IngameState* parent) : m_parent{parent} {};
    virtual void update(double delta) = 0;
    virtual void draw(sf::RenderWindow& window) {
        window.draw(m_sprite);
    };

    virtual void setPosition(sf::Vector2f pos) {
        m_sprite.setPosition(pos);
    }
protected:
    IngameState* m_parent;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

