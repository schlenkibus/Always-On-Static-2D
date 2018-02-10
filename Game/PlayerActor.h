#pragma once

#include "GameActor.h"

class animationObjectTakesRefSprite;

class PlayerActor : public GameActor {
public:
    PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name);
    void update(double delta) override;
    void playOnce();
    bool isPlaying();
    void getDamage();
    void stopDamage();
protected:
    void selectTexture(size_t index);


	bool m_isJumping = false;
    bool m_hasDamage = false;
    bool m_isRed = false;
    size_t m_currentFrameIndex;
    bool playing = false;
    bool shouldStepAnim();
    sf::Clock clock;
    std::vector<sf::Texture> m_textures;
    sf::Time m_frameLenght;

};