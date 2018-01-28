#pragma once

#include "GameActor.h"

class animationObjectTakesRefSprite;

class PlayerActor : public GameActor {
public:
    PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name);
    void update(double delta) override;
protected:
    std::shared_ptr<animationObjectTakesRefSprite> m_anim;
};