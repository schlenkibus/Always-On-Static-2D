#include <iostream>
#include "IngameState.h"
#include "../Tools/TimeUtils.h"

IngameState::IngameState() : GameState() {
    m_world = std::make_unique<PhysicsWorld>();
    m_labels.push_back(std::make_unique<Label>(sf::Vector2f(0, 0), "fps", [](Label* l){
        l->setText(std::string("fps: ") + std::to_string(TimeUtils::FPS::getFPS()));
    }));

    m_world->addActor(std::make_shared<GameActor>(*m_world.get(), Application::get().getResourceManager().getTexture("floor.png"),
                                                   sf::Vector2f(0, 700), std::string("floor"), true));

    m_world->addActor(std::make_shared<PlayerActor>(*m_world.get(), Application::get().getResourceManager().getTexture("player.png"),
                                                   sf::Vector2f(100, 200), std::string("player")));
}

IngameState::~IngameState() {

}

void IngameState::update(double deltaTime) {
    m_world->update(deltaTime);

    if(TimeUtils::Physics::shouldUpdatePhysics())
        m_world->updatePhysics();


    for(auto& l: m_labels) {
        l->update(deltaTime);
    }
}

void IngameState::draw(sf::RenderWindow &window) {
    m_world->draw(window);

    for(auto& l: m_labels) {
        l->draw(window);
    }
}
