#pragma once


#include "gameObject.h"

class animatedGenericGameObject : public gameObject {
public:
    animatedGenericGameObject(IngameState* parent, std::string pathToAnimFolder,sf::Time frameLenght);
    void update(double delta) override;
    void playOnce();
    bool isPlaying();
protected:
    void selectTexture(size_t index);

    size_t m_currentFrameIndex;
    bool playForward = true;
    bool playing = false;
    bool shouldStepAnim();
    sf::Clock clock;
    std::vector<sf::Texture> m_textures;
    sf::Time m_frameLenght;
};
