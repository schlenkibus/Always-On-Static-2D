#include <iostream>
#include <thread>
#include "Application.h"
#include "Tools/TimeUtils.h"
#include "GameStates/MenuGameState.h"
#include <SFML/Network.hpp>
#include "GameStates/IngameState.h"
#include "Tools/UDPLayer.h"
#include <fstream>
#include <cctype>
#include "GameStates\SplashScreen.h"

Application::Application() : m_window(sf::VideoMode(1366,768), "Alway On Static", sf::Style::Close),
currentState{}, m_resourceManager{}, m_remoteGameState{ "" }, m_currLock{ false }, m_remoteLock{ false }, m_messageLock{ false } {
	m_window.setFramerateLimit(60);
}

Application& Application::get() {
    static Application theApp;
    return theApp;
}

double Application::getSignalLenght() {
	return m_symbolLenghtInSec;
}

void Application::shortenSignalLenght() {
	if (m_symbolLenghtInSec > 2.75) {
		m_symbolLenghtInSec = m_symbolLenghtInSec - 0.1f;
	}
}

sf::IpAddress Application::getIpAdress() {
    return m_ip;
}

int Application::run() {

    m_music.openFromFile("Resources/ggj_temp1.wav");

    m_music.setLoop(true);
    m_music.play();

    currentState.reset(std::make_unique<SplashScreen>().release());

    std::thread network(UDPLayer::run);

    sf::Event event;
    while(m_window.isOpen()) {
        while(m_window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                m_window.close();
                network.join();
                quit();
                return 0;
            } if(event.type == sf::Event::TextEntered) {
                if(auto menu = dynamic_cast<MenuGameState*>(currentState.get())) {
                    menu->textEntered(event);
                }
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
    if(currentState != nullptr) {
        currentState->update(00);
    }
}

void Application::onMessageRecieved(std::string buffer) {


    if(buffer.find("g:r") != std::string::npos) {
		m_remoteLock = true;
		m_currLock = true;

        m_remoteGameState = "g:r";
        m_currentGameState = "g:p";

		m_remoteLock = false;
		m_currLock = false;
        return;
    }
    if(currentState != nullptr) {
        currentState->onMessageRecieved(buffer);
    }
}

void Application::sendMessage(std::string message) {
	//while (m_messageLock) {
		//std::cout << "messagelock\n";
	//}

	m_messageLock = true;

    m_messageQueue.push(message);

	m_messageLock = false;
}

void Application::setGameState(std::string state) {
	//while (m_currLock) {
		//std::cout << "currlock or remotelock\n";
	//}

	m_currLock = true;

    m_currentGameState = state;

	m_currLock = false;
}

std::string Application::getGameState() {
	//while (m_currLock) {
		//std::cout << "currlock or remotelock\n";
	//}

	m_currLock = true;

	auto temp = m_currentGameState;

	m_currLock = false;

    return temp;
}

std::string Application::getMessageToSend() {
	//while (m_messageLock) {
		//std::cout << "messagelock\n";
	//}

	m_messageLock = true;

    if(!m_messageQueue.empty()) {
        auto message = std::string(m_messageQueue.front());
        m_messageQueue.pop();

		m_messageLock = false;
        return std::move(message);
    } else {
		m_messageLock = false;
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

void Application::setIp(std::string ip) {
    m_ip = ip;
}

IngameState* Application::getIngameGameState() {
    if(auto ingame = dynamic_cast<IngameState*>(currentState.get())) {
        return ingame;
    }
    return nullptr;
}

std::string Application::getSavedIp() {
	try {
		std::ifstream s("lastip");
		std::string line;

		std::getline(s, line);
		//std::cout << "line: " << line;
		if (line.empty())
			return "enter ip";

		return std::move(line);
	}
	catch (...) {
		return "file not preset!";
	}
}
void Application::saveIp(std::string ip) {
	std::cerr << ip << std::endl;

	std::ofstream s("lastip");
	auto ipCstr = ip;
	//std::cout << "cstr: " << ip.c_str() << std::endl;
	s.write(ip.c_str(), sizeof(ipCstr));
	s.close();
}

std::string Application::getCurrentGameSymbol() {
    if(auto ingameState = dynamic_cast<IngameState*>(currentState.get())) {
        return ingameState->getSymbol();
    } else {
        return "";
    }
}

std::string Application::getRemoteGameState() {

	m_remoteLock = true;

	std::string temp;

	temp = m_remoteGameState;
	m_remoteLock = false;

    return  temp;
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