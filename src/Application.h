#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameStates/GameState.h"
#include "ResourceManagement/ResourceManager.h"
#include <Box2D/Box2D.h>

class Application {
public:
    static Application& get();
    int run();
    sf::Vector2u getWindowSize();
    sf::RenderWindow& getWindow();
    ResourceManager& getResourceManager();
    void installState(std::unique_ptr<GameState> newState);
    void quit();
private:
    void draw();
    void update();
    Application();
    sf::RenderWindow m_window;
    std::unique_ptr<GameState> currentState;
    ResourceManager m_resourceManager;
};
