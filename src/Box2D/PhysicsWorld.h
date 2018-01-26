#pragma once
#include <Box2D/Box2D.h>
#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>
#include "../Game/GameActor.h"
#include "../Game/PlayerActor.h"


class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld();

    void update(double delta);
    void updatePhysics();
    void draw(sf::RenderWindow& window);

    //template<class T> std::shared_ptr<GameActor> addActor(std::shared_ptr<T> actor);
    template<class T> std::shared_ptr<GameActor> addActor(std::shared_ptr<T> actor) {
        m_actors[actor->getName()] = actor;
        return m_actors[actor->getName()];
    }

    std::shared_ptr<GameActor> getActor(std::string name);

    b2Body* addBody(std::string name, std::shared_ptr<b2BodyDef> bodydef);
    b2Body* getBody(std::string name);
    b2World* getWorld();
private:
    b2World m_world;
    std::unordered_map<std::string, b2Body*> m_bodys;
    std::map<std::string, std::shared_ptr<GameActor>> m_actors;
};
