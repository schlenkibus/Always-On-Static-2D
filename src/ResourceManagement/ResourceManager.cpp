#include <cassert>
#include <iostream>
#include "ResourceManager.h"

ResourceManager::ResourceManager() {

}

sf::Texture& ResourceManager::getTexture(std::string file) {
    std::map<std::string, sf::Texture>::iterator a = m_textures.find(file);

    if (a != m_textures.end())
        return a->second;

    if (!m_textures[file].loadFromFile("./Resources/" + file))
        assert(false);

    return m_textures[file];
}