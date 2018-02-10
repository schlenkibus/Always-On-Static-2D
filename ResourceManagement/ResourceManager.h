#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>

class ResourceManager {
public:
    ResourceManager();
    sf::Texture& getTexture(std::string file);
private:
    std::map<std::string, sf::Texture> m_textures;
};