#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "GameStates/GameState.h"
#include "ResourceManagement/ResourceManager.h"
#include <Box2D/Box2D.h>
#include <queue>
#include <SFML/Network/IpAddress.hpp>

class IngameState;

class Application {
public:
    static Application& get();
    int run();

    sf::Vector2u getWindowSize();
    sf::RenderWindow& getWindow();
    ResourceManager& getResourceManager();

    void installState(std::unique_ptr<GameState> newState);

    std::string getCurrentGameSymbol();
    std::string getRemoteGameState();

    void onMessageRecieved(std::string message);
    void sendMessage(std::string message);

    void setGameState(std::string state);
    std::string getGameState();
    sf::IpAddress getIpAdress();
    std::string getMessageToSend();
    void quit();
    void setIp(std::string ip);

    IngameState* getIngameGameState();
private:
    void draw();
    void update();
    Application();
    sf::RenderWindow m_window;
    std::unique_ptr<GameState> currentState;
    ResourceManager m_resourceManager;
    std::queue<std::string> m_messageQueue;
    std::string m_remoteGameState;
    std::string m_currentGameState;
    sf::IpAddress m_ip;

    sf::Music m_music;
};
