#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Label {
public:
    Label(sf::Vector2f pos, std::string text);
    Label(sf::Vector2f pos, std::string text, std::function<void(Label*)> updateFunction);
    void draw(sf::RenderWindow& window);
    void update(double delta);
    void setText(std::string s);
private:
    sf::Text m_text;
    sf::Font m_font;
    std::function<void(Label*)> m_updateFunction;
};
