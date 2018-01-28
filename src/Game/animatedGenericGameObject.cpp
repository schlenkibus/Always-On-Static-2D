//
// Created by justus on 28.01.18.
//

#include "animatedGenericGameObject.h"
#include <experimental/filesystem>

std::vector<std::string> getPathListOfDirectory(std::string directory)
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

animatedGenericGameObject::animatedGenericGameObject(IngameState* parent,
                                                     std::string pathToAnimFolder,
                                                     sf::Time frameLenght)
        : gameObject(parent), m_frameLenght(frameLenght) {
    for(auto file: getPathListOfDirectory(pathToAnimFolder)) {
        sf::Texture tex;
        tex.loadFromFile(file);
        m_textures.push_back(tex);
    }
    selectTexture(0);
}

void animatedGenericGameObject::selectTexture(size_t index) {
    m_currentFrameIndex = index;
    m_sprite.setTexture(m_textures[index]);
}

bool animatedGenericGameObject::shouldStepAnim() {
    auto curr = clock.getElapsedTime();
    if(curr.asSeconds() > m_frameLenght.asSeconds()) {
        clock.restart();
        return true;
    }
    return false;
}

void animatedGenericGameObject::playOnce() {
    playing = true;
}

void animatedGenericGameObject::update(double delta) {
    if(playing) {
        if (shouldStepAnim()) {
            if (playForward) {
                if (m_currentFrameIndex + 1 < m_textures.size()) {
                    m_currentFrameIndex++;
                    selectTexture(m_currentFrameIndex);
                } else {
                    playForward = false;
                }
            } else {
                if (m_currentFrameIndex - 1 > 0) {
                    m_currentFrameIndex--;
                    selectTexture(m_currentFrameIndex);
                } else {
                    playForward = true;
                    playing = false;
                }
            }
        }
    }
}