#pragma once

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "gameObject.h"

class IngameState;

class staticNoiseActor : public gameObject {
public:
    staticNoiseActor(IngameState* parent);
    void update(double delta) override;
protected:
    sf::Image calculateTransmissionPicture();
    sf::Color calculateTransmissionPixelColor();

    std::vector<sf::Image> m_transmissionImages;
    sf::Image m_screenOverlayImage;
};
