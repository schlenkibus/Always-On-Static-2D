#pragma once


#include "animatedGenericGameObject.h"

class animationObjectTakesRefSprite : public animatedGenericGameObject {
public:
    animationObjectTakesRefSprite(IngameState* parent, std::string pathToAnimFolder,sf::Time frameLenght, sf::Sprite& target);

    virtual void setPosition(sf::Vector2f pos) override {
        m_target.setPosition(pos);
    }

    sf::Sprite& getSprite() {
        return m_target;
    }
private:
    void selectTexture(size_t index);
    sf::Sprite& m_target;
};


