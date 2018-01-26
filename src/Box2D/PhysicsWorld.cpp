#include <iostream>
#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld() : m_world{b2Vec2(0.0f, -9.81f)} {

}
PhysicsWorld::~PhysicsWorld() {

}

void PhysicsWorld::update(double delta) {


    for(std::pair<std::string, std::shared_ptr<GameActor>> actor: m_actors) {
        actor.second->update(delta);
    }
}

void PhysicsWorld::updatePhysics() {
    m_world.Step(1/60.f, 6, 2);
}

void PhysicsWorld::draw(sf::RenderWindow& window) {
    for(std::pair<std::string, std::shared_ptr<GameActor>> actor: m_actors) {
        actor.second->draw(window);
    }
}

/*std::shared_ptr<GameActor> PhysicsWorld::addActor(std::shared_ptr<PlayerActor> actor) {
    m_actors[actor->getName()] = actor;
    return m_actors[actor->getName()];
}
/*
std::shared_ptr<GameActor> PhysicsWorld::addActor(std::shared_ptr<GameActor> actor) {
    m_actors[actor->getName()] = actor;
    return m_actors[actor->getName()];
}
*/
std::shared_ptr<GameActor> PhysicsWorld::getActor(std::string name) {
    return m_actors[name];
}

b2Body* PhysicsWorld::addBody(std::string name, std::shared_ptr<b2BodyDef> bodydef) {
    auto body = m_world.CreateBody(bodydef.get());
    m_bodys[name] = body;
    return body;
}

b2Body* PhysicsWorld::getBody(std::string name) {
    return m_bodys[name];
}

b2World* PhysicsWorld::getWorld() {
    return &m_world;
}

