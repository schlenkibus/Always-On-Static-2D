#pragma once

#include "GameState.h"
#include "../GUI/Label.h"
#include "../Box2D/PhysicsWorld.h"

class IngameState : public GameState {
public:
    IngameState();
    ~IngameState();
    void update(double deltaTime) override;
    void draw(sf::RenderWindow &window) override;
private:
    std::vector<std::unique_ptr<Label>> m_labels;
    std::unique_ptr<PhysicsWorld> m_world;
};
