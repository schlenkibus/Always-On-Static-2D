#include <iostream>
#include "Application.h"
#include "Tools/TimeUtils.h"
#include "GameStates/MenuGameState.h"

Application::Application() : m_window(sf::VideoMode(1366,768), "GGJ", sf::Style::Fullscreen),
                             currentState{}, m_resourceManager{} {
}

Application& Application::get() {
    static Application theApp;
    return theApp;
}


int Application::run() {
    currentState.reset(std::make_unique<MenuGameState>().release());

    sf::Event event;
    while(m_window.isOpen()) {
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
                quit();
                return 0;
            }
        }
        update();
        m_window.clear();
        draw();
        m_window.display();
    }
}

void Application::update() {
    auto delta = TimeUtils::getDeltaTime();

    if(currentState != nullptr) {
        currentState->update(delta);
    }
}

void Application::draw() {
    if(currentState != nullptr) {
        currentState->draw(m_window);
    }
}

void Application::quit() {
    //TODO install quitscreen
    //currentState.reset(std::make_unique<QuitScreenState>().release());
    exit(0);
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