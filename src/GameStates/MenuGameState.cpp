#include <iostream>
#include "MenuGameState.h"
#include "../Application.h"
#include "../Tools/TimeUtils.h"
#include "IngameState.h"

MenuGameState::MenuGameState() : GameState(), m_buttons{}, m_labels{} {
    auto windowSize = Application::get().getWindowSize();

    m_buttons.push_back(std::make_unique<Button>([](){
        Application::get().installState(std::make_unique<IngameState>());
    }, "Play", Application::get().getResourceManager().getTexture("buttonTexture.png"), sf::Vector2f(windowSize.x/ 2, windowSize.y / 2 - 100)));

    m_buttons.push_back(std::make_unique<Button>([](){
        Application::get().quit();
    }, "Exit", Application::get().getResourceManager().getTexture("buttonTexture.png"), sf::Vector2f(windowSize.x / 2, windowSize.y / 2)));

    m_labels.push_back(std::make_unique<Label>(sf::Vector2f(0,0), "FPS", [](Label* l) {
        l->setText(std::string("fps: ") + std::to_string(TimeUtils::FPS::getFPS()));
    }));

}

MenuGameState::~MenuGameState() {

}

void MenuGameState::update(double deltaTime) {
    for(auto& button: m_buttons)
        button->update(deltaTime);

    for(auto& label: m_labels)
        label->update(deltaTime);
}

void MenuGameState::draw(sf::RenderWindow& window) {
    for(auto& button: m_buttons)
        button->draw(window);

    for(auto& label: m_labels)
        label->draw(window);
}