#include <experimental/filesystem>
#include "genericMultiAnimationGameObject.h"
#include <map>

std::vector<std::string> getPathListOfDirectory2(std::string directory)
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

std::vector<sf::Texture> loadTextures(std::vector<std::string> paths) {
    std::vector<sf::Texture> list;
    for(auto p: paths) {
        sf::Texture t;
        t.loadFromFile(p);
        list.push_back(t);
    }
    return list;
}

genericMultiAnimationGameObject::genericMultiAnimationGameObject(IngameState *parent,
                                                                 const std::map<std::string, std::string> animTofolder,
                                                                 const std::map<std::string, sf::Time> animToFrametime) : gameObject(parent) {
    for(auto it = animTofolder.begin(); it != animTofolder.end(); it++) {
        m_animationMap[it->first] = loadTextures(getPathListOfDirectory2(it->second));
    }

    for(auto it = animToFrametime.begin(); it != animToFrametime.end(); it++) {
        m_animTimings[it->first] = it->second;
    }

    playOnce("idle");
}

void genericMultiAnimationGameObject::playOnce(std::string animName) {
    if(!m_animationMap[animName].empty()) {
        m_currAnimName = animName;
        currAnimation = &m_animationMap[animName];
        playing = true;
    }
}

void genericMultiAnimationGameObject::selectTexture(size_t index) {
    m_currentFrameIndex = index;
    m_sprite.setTexture(currAnimation->at(index));
}

bool genericMultiAnimationGameObject::shouldStepAnim() {
    auto curr = clock.getElapsedTime();
    auto currFrameLenght = m_animTimings[m_currAnimName];
    if(curr.asSeconds() > currFrameLenght.asSeconds()) {
        clock.restart();
        return true;
    }
    return false;
}



void genericMultiAnimationGameObject::update(double delta) {
    if(currAnimation != nullptr) {
        if (playing) {
            if (shouldStepAnim()) {
                if (playForward) {
                    if (m_currentFrameIndex + 1 < currAnimation->size()) {
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
                        playOnce("idle");
                    }
                }
            }
        }
    }
}