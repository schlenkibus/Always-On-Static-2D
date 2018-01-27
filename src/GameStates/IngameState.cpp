#include <iostream>
#include "IngameState.h"
#include "../Tools/TimeUtils.h"
#include "../Game/genericGameObject.h"

IngameState::IngameState() : GameState(), m_transmissionRate(100), m_currentCorrectSymbol{symbol::x} {
    m_world = std::make_unique<PhysicsWorld>();

    m_gameObjects["staticNoise"] = std::make_unique<staticNoiseActor>(this);
    m_gameObjects["tv"] = std::make_unique<genericGameObject>(this, Application::get().getResourceManager().getTexture("fernseher.png"));

    m_labels.push_back(std::make_unique<Label>(sf::Vector2f(0, 50), "rate: ", [this](Label* l){
        l->setText(std::string("rate: ") + std::to_string(getTransmissionRate()));
    }));
}

IngameState::~IngameState() {

}

void IngameState::onMessageRecieved(std::string message) {
    m_transmissionRate = atoi(message.c_str());
}

void IngameState::update(double deltaTime) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        m_currentCorrectSymbol = symbol::x;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        m_currentCorrectSymbol = symbol::y;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        m_currentCorrectSymbol = symbol::z;
    }

    m_gameObjects["staticNoise"]->update(deltaTime);

    m_world->update(deltaTime);
    if(TimeUtils::Physics::shouldUpdatePhysics())
        m_world->updatePhysics();

    for(auto& l: m_labels) {
        l->update(deltaTime);
    }
}



const char* IngameState::getSymbol() {
    switch(m_currentCorrectSymbol) {
        case symbol::x:
            return "s:x";
        case symbol::y:
            return "s:y";
        case symbol::z:
            return "s:z";
        default:
            return "NAN";
    }
}

void IngameState::draw(sf::RenderWindow &window) {
    m_world->draw(window);

    m_gameObjects["staticNoise"]->draw(window);
    m_gameObjects["tv"]->draw(window);

    for(auto& l: m_labels) {
        l->draw(window);
    }
}

int IngameState::getTransmissionRate() {
    return m_transmissionRate;
}

void IngameState::setTransmissionRate(int r) {
    m_transmissionRate = r;
}