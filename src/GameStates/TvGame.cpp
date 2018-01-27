//
// Created by justus on 27.01.18.
//

#include <iostream>
#include "TvGame.h"
#include "../Tools/TimeUtils.h"

TvGame::TvGame(PhysicsWorld *parent) : m_parent(parent) {

    m_label = std::make_unique<Label>(sf::Vector2f(374, 86), "Lifes: ", [this](Label* l){
        if(isGameOver()) {
            l->setPosition(sf::Vector2f(585, 249));
            l->setText("Game Over!");
        }
        else {
            l->setText(std::string("Lifes: ") + std::to_string(getLifes()));
        }
    });

    m_obstacles.push_back(std::make_unique<tvGameObject>(Application::get().getResourceManager().getTexture("tv/cacti.png"), sf::Vector2f(1100, 295), nullptr));

    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/ground.png"), sf::Vector2f(363, 420), std::string("ground"), true));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/dino.png"), sf::Vector2f(440, 317), std::string("dino"), false));
    parent->getActor("dino")->getBody()->SetGravityScale(2);
}

void TvGame::update(double delta) {

    m_label->update(delta);



    if(m_gameOver == false) {

        auto playerActor = m_parent->getActor("dino");

        if(TimeUtils::Physics::shouldUpdatePhysics()) {
            for(auto& obstacle: m_obstacles)
                obstacle->getSprite().move(sf::Vector2f(m_speed * delta / 1500, 0));
        }



        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            playerActor->getBody()->GetLinearVelocity().y == 0 &&
            TimeUtils::Logic::canJump()) {
            playerActor->getBody()->SetLinearVelocity(b2Vec2(0, 500));
            playerActor->getBody()->ApplyLinearImpulse(b2Vec2(0, 500), playerActor->getBody()->GetWorldCenter(), true);


        }



        for(auto& obs: m_obstacles) {
            if(playerActor->getSprite().getGlobalBounds().intersects(obs->getSprite().getGlobalBounds()) && TimeUtils::Logic::canJump())
            {
                std::cout << "hit!\n";
                m_lifes--;
                if (m_lifes == 0) {
                    m_gameOver = true;
                    installGameOver();
                }
            }
        }

        for(auto& obs: m_obstacles) {
            if(obs->getSprite().getGlobalBounds().left < 360) {
                obs->getSprite().setPosition(1100, 295);
            }
        }
    }
}

void TvGame::installGameOver() {

}

void TvGame::draw(sf::RenderWindow& window) {
    for(auto& obs: m_obstacles) {
        obs->draw(window);
    }

    m_label->draw(window);
}

bool TvGame::isGameOver() {
    return m_gameOver;
}

int TvGame::getLifes() {
    return m_lifes;
}

