#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "../GUI/TextInput.h"

class MenuGameState : public GameState {
public:
    MenuGameState();
    ~MenuGameState();
    void update(double deltaTime);
    void draw(sf::RenderWindow& window);
    void onMessageRecieved(std::string message);
    void textEntered(sf::Event& event);
private:
	sf::Sprite m_background;
    std::vector<std::unique_ptr<Button>> m_buttons;
    std::vector<std::unique_ptr<Label>> m_labels;
	std::unique_ptr<TextInput> m_ipBox;
};