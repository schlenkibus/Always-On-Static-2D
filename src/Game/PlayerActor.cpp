//
// Created by justus on 23.01.18.
//

#include <iostream>
#include "PlayerActor.h"
#include "../GameStates/IngameState.h"
#include "../Tools/TimeUtils.h"
#include "animationObjectTakesRefSprite.h"

PlayerActor::PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name) : GameActor(w, tex, pos, name, false) {
    std::string directory = "Resources/tv/dino/";
    IngameState* state = Application::get().getIngameGameState();
    m_anim = std::make_shared<animationObjectTakesRefSprite>(state, directory, sf::seconds(0.2), m_sprite);
    m_anim->setPosition(pos);
}

void PlayerActor::update(double delta) {

    m_anim->update(delta);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        getBody()->GetLinearVelocity().y == 0 &&
        TimeUtils::Logic::canJump()) {
        Application::get().getIngameGameState()->animLeftHand();
        getBody()->SetLinearVelocity(b2Vec2(0, 200));
        getBody()->ApplyLinearImpulse(b2Vec2(0, 200), getBody()->GetWorldCenter(), true);
    }

    if(!m_anim->isPlaying()) {
        m_anim->playOnce();
    }

    GameActor::update(delta);
}
