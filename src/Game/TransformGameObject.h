#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class TransformGameObject {
public:
    TransformGameObject(sf::Texture& tex, sf::Vector2f pos, std::string name);
    void update(double delta);
    void draw(sf::RenderWindow& window);

};