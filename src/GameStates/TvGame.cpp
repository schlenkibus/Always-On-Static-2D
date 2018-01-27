//
// Created by justus on 27.01.18.
//

#include <iostream>
#include "TvGame.h"
#include "../Tools/TimeUtils.h"

TvGame::TvGame(PhysicsWorld *parent) : m_parent(parent) {

    m_label.push_back(std::make_unique<Label>(sf::Vector2f(374, 86), "Lifes: ", [this](Label* l){
        if(isGameOver()) {
            l->setPosition(sf::Vector2f(585, 239));
            l->setText("Game Over!");
        }
        else {
            l->setText(std::string("Lifes: ") + std::to_string(getLifes()));
        }
    }));

    m_label.push_back(std::make_unique<Label>(sf::Vector2f(374, 106), "Score: ", [this](Label* l){
        if(isGameOver()) {
            l->setPosition(sf::Vector2f(585, 269));
            l->setText("Final Score: " + std::to_string(getScore()));
        }
        else {
            l->setText(std::string("Score: ") + std::to_string(getScore()));
        }
    }));

    m_obstacle = std::make_unique<tvGameObject>(Application::get().getResourceManager().getTexture("tv/cacti.png"), sf::Vector2f(1100, 305), nullptr);

    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/ground.png"), sf::Vector2f(363, 420), std::string("ground"), true));
    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/dino.png"), sf::Vector2f(440, 317), std::string("dino"), false));
    parent->getActor("dino")->getBody()->SetGravityScale(6);
}

int TvGame::getScore() {
    return m_score;
}

void TvGame::update(double delta) {

    if(Application::get().getGameState() != "g:p")
        return;

    for(auto& l: m_label) {
       l->update(delta);
    }

    if(!m_gameOver) {
        auto playerActor = m_parent->getActor("dino");

        if(TimeUtils::Physics::shouldUpdatePhysics()) {
            m_obstacle->getSprite().move(sf::Vector2f(m_speed * delta, 0));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
            playerActor->getBody()->GetLinearVelocity().y == 0 &&
            TimeUtils::Logic::canJump()) {
            playerActor->getBody()->SetLinearVelocity(b2Vec2(0, 200));
            playerActor->getBody()->ApplyLinearImpulse(b2Vec2(0, 200), playerActor->getBody()->GetWorldCenter(), true);
        }

        if(!m_tookDamage &&
           playerActor->getSprite().getGlobalBounds().intersects(m_obstacle->getSprite().getGlobalBounds()))
        {
            m_lifes--;
            m_tookDamage = true;
            if (m_lifes == 0) {
                m_gameOver = true;
                installGameOver();
            }
        }

        if(m_obstacle->getSprite().getGlobalBounds().left < 330) {
            if(!m_tookDamage)
                m_score++;
            m_obstacle->getSprite().setPosition(1100, 305);
            m_tookDamage = false;
        }
    }
}

void TvGame::installGameOver() {
    Application::get().setGameState("g:o");
}

void TvGame::draw(sf::RenderWindow& window) {
    m_obstacle->draw(window);

    for(auto& l: m_label)
        l->draw(window);
}

bool TvGame::isGameOver() {
    return m_gameOver;
}

int TvGame::getLifes() {
    return m_lifes;
}

