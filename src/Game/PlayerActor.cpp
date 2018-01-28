//
// Created by justus on 23.01.18.
//

#include <iostream>
#include "PlayerActor.h"
#include "../GameStates/IngameState.h"
#include "../Tools/TimeUtils.h"
#include <experimental/filesystem>

std::vector<std::string> getPathListOfDirectory4(std::string directory)
{
    std::vector<std::string> list;
    auto p = std::experimental::filesystem::path(directory.c_str());
    for(auto dirEntry: std::experimental::filesystem::directory_iterator(p))
    {
        if(std::experimental::filesystem::is_directory(dirEntry.path()) == false)
        {
            list.push_back(dirEntry.path().string());
        }
    }
    std::sort(list.begin(), list.end());
    return list;
}

PlayerActor::PlayerActor(PhysicsWorld& w, sf::Texture& tex, sf::Vector2f pos, std::string name) : GameActor(w, tex, pos, name, false) {
    IngameState* state = Application::get().getIngameGameState();
    for(auto file: getPathListOfDirectory4("Resources/tv/dino/")) {
        sf::Texture tex;
        tex.loadFromFile(file);
        m_textures.push_back(tex);
    }
    m_frameLenght = sf::seconds(0.2);
    m_currentFrameIndex = 0;
    selectTexture(0);

}

void PlayerActor::selectTexture(size_t index) {
    m_currentFrameIndex = index;
    m_sprite.setTexture(m_textures[index]);
}

bool PlayerActor::shouldStepAnim() {
    auto curr = clock.getElapsedTime();
    if(curr.asSeconds() > m_frameLenght.asSeconds()) {
        clock.restart();
        return true;
    }
    return false;
}

void PlayerActor::playOnce() {
    playing = true;
}

bool PlayerActor::isPlaying() {
    return playing;
}

void PlayerActor::update(double delta) {

    if(playing) {
        if (shouldStepAnim()) {
            if (m_currentFrameIndex + 1 < m_textures.size()) {
                m_currentFrameIndex++;
                selectTexture(m_currentFrameIndex);
            } else {
                m_currentFrameIndex = -1;
                playing = false;
            }
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        getBody()->GetLinearVelocity().y == 0 &&
        TimeUtils::Logic::canJump()) {
        Application::get().getIngameGameState()->animLeftHand();
        getBody()->SetLinearVelocity(b2Vec2(0, 200));
        getBody()->ApplyLinearImpulse(b2Vec2(0, 200), getBody()->GetWorldCenter(), true);
    }

    if(!isPlaying()) {
        playOnce();
    }

    GameActor::update(delta);
}