//
// Created by justus on 28.01.18.
//

#include "animationObjectTakesRefSprite.h"


animationObjectTakesRefSprite::animationObjectTakesRefSprite(IngameState* parent,
                                                             std::string pathToAnimFolder,
                                                             sf::Time frameLenght,
                                                             sf::Sprite& target) :
        animatedGenericGameObject(parent, pathToAnimFolder, frameLenght), m_target(target) {
}

void animationObjectTakesRefSprite::selectTexture(size_t index) {
    m_currentFrameIndex = index;
    m_target.setTexture(m_textures[index]);
}