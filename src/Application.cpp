#include <iostream>
#include <thread>
#include "Application.h"
#include "Tools/TimeUtils.h"
#include "GameStates/MenuGameState.h"
#include "SFML/Network.hpp"
#include "GameStates/IngameState.h"
#include "Tools/UDPLayer.h"

Application::Application() : m_window(sf::VideoMode(1366,768), "GGJ", sf::Style::Fullscreen),
                             currentState{}, m_resourceManager{}, m_remoteGameState{""} {
}

Application& Application::get() {
    static Application theApp;
    return theApp;
}

int Application::run() {
    setGameState("g:m");

    currentState.reset(std::make_unique<MenuGameState>().release());

    std::thread network(UDPLayer::run);

    sf::Event event;
    while(m_window.isOpen()) {
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
                network.join();
                quit();
                return 0;
            }
        }
        update();
        m_window.clear();
        draw();
        m_window.display();
    }
    network.join();
}

void Application::update() {
    auto delta = TimeUtils::getDeltaTime();

    if(currentState != nullptr) {
        currentState->update(delta);
    }
}

void Application::onMessageRecieved(std::string buffer) {

    if(buffer.find("g") != std::string::npos) {
        m_remoteGameState = buffer;
        return;
    }
    if(currentState != nullptr) {
        currentState->onMessageRecieved(buffer);
    }
}

void Application::sendMessage(std::string message) {
    m_messageQueue.push(message);
}

void Application::setGameState(std::string state) {
    m_currentGameState = state;
}

std::string Application::getGameState() {
    return m_currentGameState;
}

std::string Application::getMessageToSend() {
    if(!m_messageQueue.empty()) {
        auto message = std::string(m_messageQueue.front());
        m_messageQueue.pop();
        return std::move(message);
    } else {
        return "";
    }
}

void Application::draw() {
    if(currentState != nullptr) {
        currentState->draw(m_window);
    }
}

void Application::quit() {
    exit(0);
}

const char* Application::getCurrentGameSymbol() {
    if(auto ingameState = dynamic_cast<IngameState*>(currentState.get())) {
        return ingameState->getSymbol();
    } else {
        return "";
    }
}

std::string Application::getRemoteGameState() {
    return m_remoteGameState;
}

void Application::installState(std::unique_ptr<GameState> newState) {
    currentState.reset(newState.release());
}

sf::Vector2u Application::getWindowSize() {
    return m_window.getSize();
}

sf::RenderWindow& Application::getWindow() {
    return m_window;
}

ResourceManager& Application::getResourceManager() {
    return m_resourceManager;
}