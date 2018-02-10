#pragma once

#include "gameObject.h"

class genericMultiAnimationGameObject : public gameObject {
public:
    genericMultiAnimationGameObject(IngameState* parent, std::map<std::string, std::string> animTofolder, std::map<std::string, sf::Time> animToFrametime);
    void update(double delta) override;
    void playOnce(std::string animName);
protected:
    void selectTexture(size_t index);

    size_t m_currentFrameIndex;
    bool playForward = true;
    bool playing = false;
    bool shouldStepAnim();
    sf::Clock clock;
    std::string m_currAnimName = "idle";
    std::vector<sf::Texture>* currAnimation;

    std::map<std::string, std::vector<sf::Texture>> m_animationMap;
    std::map<std::string, sf::Time> m_animTimings;
};


