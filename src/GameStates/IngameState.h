#pragma once

#include "GameState.h"
#include "../GUI/Label.h"
#include "../Box2D/PhysicsWorld.h"
#include "../Game/staticNoiseActor.h"

class IngameState : public GameState {

protected:
    enum symbol {
        x,y,z
    };
public:
    IngameState();
    ~IngameState();
    void update(double deltaTime) override;
    void draw(sf::RenderWindow &window) override;
    void onMessageRecieved(std::string message) override;
    int getTransmissionRate();
    void setTransmissionRate(int r);
    const char* getSymbol();
private:
    std::map<std::string, std::unique_ptr<gameObject>> m_gameObjects;

    std::vector<std::unique_ptr<Label>> m_labels;
    std::unique_ptr<PhysicsWorld> m_world;
    symbol m_currentCorrectSymbol;
    int m_transmissionRate;
};
