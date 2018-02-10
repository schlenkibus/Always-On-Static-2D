#pragma once

#include <SFML/Graphics/Texture.hpp>
#include "gameObject.h"

class genericGameObject : public gameObject {
public:
    genericGameObject(IngameState* parent, sf::Texture& tex);
    void update(double delta) override;
};