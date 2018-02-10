#include <iostream>
#include "MenuGameState.h"
#include "../Application.h"
#include "../Tools/TimeUtils.h"
#include "IngameState.h"
#include "../GUI/TextInput.h"
#include "CreditScreen.h"

MenuGameState::MenuGameState() : GameState(), m_buttons{}, m_labels{} {
    auto windowSize = Application::get().getWindowSize();

	m_background.setTexture(Application::get().getResourceManager().getTexture("StartScreenNEW.png"));



    Application::get().setGameState("g:m");

    m_buttons.push_back(std::make_unique<Button>([&](){
		Application::get().setIp(m_ipBox->getText());
		Application::get().saveIp(m_ipBox->getText());
        Application::get().installState(std::make_unique<IngameState>());
    }, "Play", Application::get().getResourceManager().getTexture("buttonTexture.png"), sf::Vector2f(1175, 374)));

    m_buttons.push_back(std::make_unique<Button>([](){
        Application::get().quit();
    }, "Exit", Application::get().getResourceManager().getTexture("buttonTexture.png"), sf::Vector2f(1175, 560)));

	m_buttons.push_back(std::make_unique<Button>([]() {
		Application::get().installState(std::make_unique<CreditScreen>());
	}, "Credits", Application::get().getResourceManager().getTexture("button2.png"), sf::Vector2f(1175, 188)));

	m_labels.push_back(std::make_unique<Label>(sf::Vector2f(60, 540), "Input Ip to play here: ", [](Label* l) {}));
	m_ipBox = std::make_unique<TextInput>(sf::Vector2f(60, 590));
	m_labels.push_back(std::make_unique<Label>(sf::Vector2f(700, 540), "Controls: ", [](Label* l) {}));
	m_labels.push_back(std::make_unique<Label>(sf::Vector2f(700, 580), "space to jump ", [](Label* l) {}));
	m_labels.push_back(std::make_unique<Label>(sf::Vector2f(700, 620), "i,o,k,l to communicate", [](Label* l) {}));
}

MenuGameState::~MenuGameState() {
}

void MenuGameState::onMessageRecieved(std::string message) {

}

void MenuGameState::textEntered(sf::Event& event) {
	m_ipBox->textEntered(event);
}

void MenuGameState::update(double deltaTime) {
    for(auto& button: m_buttons)
        button->update(deltaTime);

    for(auto& label: m_labels)
        label->update(deltaTime);

	m_ipBox->update(deltaTime);
}

void MenuGameState::draw(sf::RenderWindow& window) {
	window.draw(m_background);

    for(auto& button: m_buttons)
        button->draw(window);

    for(auto& label: m_labels)
        label->draw(window);
	
	m_ipBox->draw(window);
}