//
// Created by justus on 27.01.18.
//

#include "staticNoiseActor.h"
#include "../Tools/TimeUtils.h"
#include "../GameStates/IngameState.h"

staticNoiseActor::staticNoiseActor(IngameState* parent) : gameObject(parent) {
    for(int i = 0; i < 20; i++) {
        m_transmissionImages.push_back(calculateTransmissionPicture());
    }
    m_screenOverlayImage = m_transmissionImages.back();
    m_texture.loadFromImage(m_screenOverlayImage);
    m_sprite.setTexture(m_texture);
    m_sprite.setScale(sf::Vector2f(2.2, 2.2));
}

void staticNoiseActor::update(double delta) {
    auto mousepos = sf::Mouse::getPosition(Application::get().getWindow());
    if(m_sprite.getGlobalBounds().contains(mousepos.x, mousepos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_parent->setTransmissionRate(rand() % 100);
    }

    if(TimeUtils::Drawing::shouldRedrawScatter()) {
        m_sprite.setColor(sf::Color(255, 255, 255, 255 - (m_parent->getTransmissionRate() * 2.55)));
        m_screenOverlayImage = m_transmissionImages[rand() % 20];
        m_texture.loadFromImage(m_screenOverlayImage);
    }
}

sf::Image staticNoiseActor::calculateTransmissionPicture() {
    sf::Image img;
    img.create(500, 300);
    for(auto y = 0; y < img.getSize().y; y++) {
        for(auto x = 0; x < img.getSize().x; x++) {
            img.setPixel(x, y, calculateTransmissionPixelColor());
        }
    }
    return img;
}

sf::Color staticNoiseActor::calculateTransmissionPixelColor() {
    sf::Uint8 grey = (rand() % 10) + 100;
    sf::Uint8 white = (rand() % 10) + 245;
    sf::Uint8 black = (rand() % 10);
    sf::Uint8 alpha = 250;
    auto what = rand() % 3;
    sf::Color c;
    c.a = alpha;
    switch(what) {
        case 0:
            c.r = grey;
            c.g = grey;
            c.b = grey;
            break;
        case 1:
            c.r = white;
            c.g = white;
            c.b = white;
            break;
        case 2:
            c.r = black;
            c.g = black;
            c.b = black;
            break;

    }
    return c;
}
