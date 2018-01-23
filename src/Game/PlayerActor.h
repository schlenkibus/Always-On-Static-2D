#pragma once

#include "GameActor.h"

class PlayerActor : public GameActor {
public:
    PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name);
    void update(double delta) override;
};