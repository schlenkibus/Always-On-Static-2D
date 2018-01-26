#include <iostream>
#include <thread>
#include "Application.h"
#include "Tools/TimeUtils.h"
#include "GameStates/MenuGameState.h"
#include "SFML/Network.hpp"

Application::Application() : m_window(sf::VideoMode(1366,768), "GGJ", sf::Style::Fullscreen),
                             currentState{}, m_resourceManager{} {
}

Application& Application::get() {
    static Application theApp;
    return theApp;
}

int Application::run() {
    currentState.reset(std::make_unique<MenuGameState>().release());

    std::thread network([](){
        std::string ip("10.3.35.173");
        sf::UdpSocket socketSend;
        sf::UdpSocket socketRec;
        socketRec.bind(22222);
        socketRec.setBlocking(false);

        socketSend.bind(55555);

        char buffer[1024];
        std::size_t received = 0;
        auto test = "HELLO";
        sf::IpAddress sender;
        unsigned short port;

        while(Application::get().getWindow().isOpen()) {
            
            socketSend.send(test, sizeof(test), ip, 55555);
            if (socketRec.receive(buffer, sizeof(buffer), received, sender, port) == sf::Socket::Done)
                std::cout << sender.toString() << " said: " << buffer << '\n';
            else
                std::cout << "nothing!\n";

        }
    });

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

void Application::draw() {
    if(currentState != nullptr) {
        currentState->draw(m_window);
    }
}

void Application::quit() {
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