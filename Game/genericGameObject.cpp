//
// Created by justus on 27.01.18.
//

#include "genericGameObject.h"


genericGameObject::genericGameObject(IngameState* parent, sf::Texture &tex) : gameObject(parent) {
    m_texture = tex;
    m_sprite.setTexture(tex);
}

void genericGameObject::update(double delta) {
    //TODO? ANIM
}