#pragma once

#include "GameState.h"
#include "../GUI/Label.h"
#include "../Box2D/PhysicsWorld.h"
#include "../Game/staticNoiseActor.h"
#include "TvGame.h"
#include "../Game/currentSymbolObject.h"
#include "../Game/animatedGenericGameObject.h"
#include <random>

class IngameState : public GameState {

protected:
    enum symbol {
        i,o,k,l,none
    };

public:
    IngameState();
    ~IngameState();
    void update(double deltaTime) override;
    void draw(sf::RenderWindow &window) override;
    void onMessageRecieved(std::string message) override;
    int getTransmissionRate();
    const char* getSymbol();

    void animLeftHand();
private:
    std::map<std::string, std::unique_ptr<gameObject>> m_gameObjects;

    void updateCurrentCorrectSymbol(double delta);
    std::default_random_engine m_generator;
    std::uniform_int_distribution<int> m_distribution;

    std::vector<std::unique_ptr<Label>> m_labels;
    std::unique_ptr<PhysicsWorld> m_world;
    symbol m_currentCorrectSymbol;
    int m_transmissionRate;
    std::unique_ptr<TvGame> m_tvGame;
};
