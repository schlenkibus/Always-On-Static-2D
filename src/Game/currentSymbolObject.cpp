//
// Created by justus on 27.01.18.
//

#include <iostream>
#include "currentSymbolObject.h"
#include "../Application.h"
#include "../Tools/TimeUtils.h"
#include "../GameStates/IngameState.h"
#include <algorithm>

currentSymbolObject::currentSymbolObject(IngameState *parent) : gameObject(parent), m_currsymbol{Application::get().getCurrentGameSymbol()} {
    moving = false;
}

void currentSymbolObject::update(double delta) {

    auto position = m_sprite.getPosition();

    auto currColor = m_sprite.getColor();
    int alpha =  30 + (255 - m_parent->getTransmissionRate() * 2.55);

    alpha = std::min(alpha, 255);

    currColor.a = alpha;
    m_sprite.setColor(currColor);

    if(position.y > 110 ) {
        moving = false;
    }

    if(moving == true && TimeUtils::Drawing::shouldMoveSymbol()) {
        m_sprite.move(0, 3);
    }

    if(moving == false && TimeUtils::Drawing::shouldHideSymbol()) {
        m_sprite.setPosition(630, -30);
    }

    if(Application::get().getCurrentGameSymbol() != m_currsymbol) {
        auto& rm = Application::get().getResourceManager();
        m_currsymbol = Application::get().getCurrentGameSymbol();
        if(m_currsymbol == "s:i") {
            m_texture = rm.getTexture("circle.png");
        } else if(m_currsymbol == "s:o") {
            m_texture = rm.getTexture("triangle.png");
        } else if(m_currsymbol == "s:k") {
            m_texture = rm.getTexture("square.png");
        } else if(m_currsymbol == "s:l") {
            m_texture = rm.getTexture("squareminuscircle.png");
        }
        moving = true;
        m_sprite.setTexture(m_texture);
        m_sprite.setPosition(630, -30);
    }
}

void currentSymbolObject::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}