#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "GamePosition.h"

class PhysicsWorld;

class GameActor {
public:
    GameActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name, bool staticActor);
    ~GameActor();
    std::string getName();
    virtual void update(double deltaTime);
    void draw(sf::RenderWindow& window);
    b2Body* getBody();
protected:
    b2Body* createBody();

    GamePosition m_position;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    b2Body* m_body;
    b2Fixture* m_fixture;
    b2BodyDef m_bodyDef;
    b2PolygonShape m_shape;
    std::string m_ActorName;
};

