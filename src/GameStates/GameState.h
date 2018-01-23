#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class GameState {
public:
    virtual void update(double deltaTime) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
};
