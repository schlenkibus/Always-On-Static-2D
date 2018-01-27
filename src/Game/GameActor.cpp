#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "GameActor.h"
#include "../Box2D/PhysicsWorld.h"

GameActor::GameActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name, bool staticActor) :
        m_texture{tex},
                                                                                              m_ActorName{std::move(name)},
                                                                                              m_bodyDef{}, m_shape{}, m_position{pos} {

    //Graphics
    m_sprite.setPosition(m_position.getAsSFML());
    m_sprite.setTexture(tex);

    //Physics

    m_shape.SetAsBox(tex.getSize().x, tex.getSize().y / 2);

    if(staticActor) {
        m_bodyDef.type = b2_staticBody;
    } else {
        m_bodyDef.type = b2_dynamicBody;
    }
    m_bodyDef.position.Set(m_position.getAsBox2D().x, m_position.getAsBox2D().y);

    m_body = w.getWorld()->CreateBody(&m_bodyDef);
    m_fixture = m_body->CreateFixture(&m_shape, 0.005f);
}

GameActor::~GameActor() {
}

std::string GameActor::getName() {
    return m_ActorName;
}

void GameActor::update(double deltaTime) {
    m_position = m_body->GetPosition();
    m_sprite.setPosition(m_position.getAsSFML().x, m_position.getAsSFML().y - m_sprite.getTexture()->getSize().y / 2);
    m_sprite.setRotation(m_body->GetAngle());
}

void GameActor::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

b2Body* GameActor::getBody() {
    return m_body;
}

sf::Sprite& GameActor::getSprite() {
    return m_sprite;
}