#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "../GUI/Button.h"
#include "../GUI/Label.h"

class MenuGameState : public GameState {
public:
    MenuGameState();
    ~MenuGameState();
    void update(double deltaTime);
    void draw(sf::RenderWindow& window);
    void onMessageRecieved(std::string message);
private:
    std::vector<std::unique_ptr<Button>> m_buttons;
    std::vector<std::unique_ptr<Label>> m_labels;
};