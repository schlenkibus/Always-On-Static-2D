#include <iostream>
#include "IngameState.h"
#include "../Tools/TimeUtils.h"
#include "../Game/genericGameObject.h"
#include "MenuGameState.h"

IngameState::IngameState() : GameState(), m_transmissionRate(0), m_currentCorrectSymbol{symbol::none}, m_distribution(0, 3) {
    m_world = std::make_unique<PhysicsWorld>();
    m_tvGame = std::make_unique<TvGame>(m_world.get());

    Application::get().setGameState("g:r");

    m_gameObjects["symbol"] = std::make_unique<currentSymbolObject>(this);
    m_gameObjects["symbol"]->setPosition(sf::Vector2f(630, 200));
    m_gameObjects["staticNoise"] = std::make_unique<staticNoiseActor>(this);
    m_gameObjects["tv"] = std::make_unique<genericGameObject>(this, Application::get().getResourceManager().getTexture("fehrnsehr_kleiner.png"));
    m_gameObjects["staticNoise"]->setPosition(sf::Vector2f(200, 50));


    m_labels.push_back(std::make_unique<Label>(sf::Vector2f(0, 00), "mouse pos: ", [this](Label* l){
        auto pos = sf::Mouse::getPosition(Application::get().getWindow());
        l->setText(std::string("x: ") + std::to_string(pos.x) + " y: " + std::to_string(pos.y));
    }));


    m_labels.push_back(std::make_unique<Label>(sf::Vector2f(0, 50), "rate: ", [this](Label* l){
        l->setText(std::string("rate: ") + std::to_string(getTransmissionRate()));
    }));

    Application::get().setGameState("g:r");
}

IngameState::~IngameState() {

}

void IngameState::onMessageRecieved(std::string message) {
    m_transmissionRate = atoi(message.c_str());
}

void IngameState::update(double deltaTime) {

    m_gameObjects["staticNoise"]->update(deltaTime);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        Application::get().installState(std::make_unique<MenuGameState>());
    }

    if(Application::get().getRemoteGameState() == "g:r") {
        return;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::I)) {
        Application::get().sendMessage("m:i");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O)) {
        Application::get().sendMessage("m:o");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::K)) {
        Application::get().sendMessage("m:k");
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L)) {
        Application::get().sendMessage("m:l");
    }

    m_gameObjects["symbol"]->update(deltaTime);
    m_tvGame->update(deltaTime);

    updateCurrentCorrectSymbol(deltaTime);

    m_world->update(deltaTime);
    if(TimeUtils::Physics::shouldUpdatePhysics())
        m_world->updatePhysics();

    for(auto& l: m_labels) {
        l->update(deltaTime);
    }
}

void IngameState::updateCurrentCorrectSymbol(double delta) {
    if(TimeUtils::Logic::isThresholdExeeded()) {
        auto roll = m_distribution(m_generator);
        switch(roll) {
            case 0:
                m_currentCorrectSymbol = symbol::i;
                break;
            case 1:
                m_currentCorrectSymbol = symbol::o;
                break;
            case 2:
                m_currentCorrectSymbol = symbol::k;
                break;
            case 3:
                m_currentCorrectSymbol = symbol::l;
                break;
        }
    }
}

const char* IngameState::getSymbol() {
    switch(m_currentCorrectSymbol) {
        case symbol::i:
            return "s:i";
        case symbol::o:
            return "s:o";
        case symbol::k:
            return "s:k";
        case symbol::l:
            return "s:l";
        default:
            return "";
    }
}

void IngameState::draw(sf::RenderWindow &window) {
    m_world->draw(window);

    m_tvGame->draw(window);
    m_gameObjects["staticNoise"]->draw(window);
    m_gameObjects["symbol"]->draw(window);
    m_gameObjects["tv"]->draw(window);


    for(auto& l: m_labels) {
        l->draw(window);
    }
}

int IngameState::getTransmissionRate() {
    return m_transmissionRate;
}