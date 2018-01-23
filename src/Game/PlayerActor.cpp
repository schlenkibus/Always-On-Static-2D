//
// Created by justus on 23.01.18.
//

#include <iostream>
#include "PlayerActor.h"

PlayerActor::PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name) : GameActor(w, tex, pos, name, false) {
}

void PlayerActor::update(double delta) {
    auto body = getBody();

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        body->ApplyForceToCenter(b2Vec2(-300, 0), true);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        body->ApplyForceToCenter(b2Vec2(300, 0), true);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        body->ApplyForceToCenter(b2Vec2(0, 600), true);
    }

    GameActor::update(delta);
}
