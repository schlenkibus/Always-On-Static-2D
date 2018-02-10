//
// Created by justus on 27.01.18.
//

#include "staticNoiseActor.h"
#include "../Tools/TimeUtils.h"
#include "../GameStates/IngameState.h"

staticNoiseActor::staticNoiseActor(IngameState* parent) : gameObject(parent) {
    for(auto i = 0; i < 20; i++) {
        m_transmissionImages.push_back(Application::get().getResourceManager().getTexture(std::string("noise/") + std::to_string(i) + ".png"));
    }
    m_texture = m_transmissionImages.back();
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(sf::Vector2f(2.2, 2.2));
}

void staticNoiseActor::update(double delta) {
    if(TimeUtils::Drawing::shouldRedrawScatter()) {
        m_sprite.setColor(sf::Color(255, 255, 255, 255 - (m_parent->getTransmissionRate() * 2.55)));
        //m_sprite.setColor(sf::Color(255, 255, 255, 50));
        m_texture = m_transmissionImages[rand() %  20];
    }
}
