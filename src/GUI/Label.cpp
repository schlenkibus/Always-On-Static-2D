#include "Label.h"
#include "../Application.h"

Label::Label(sf::Vector2f pos, std::string text) {
    m_font.loadFromFile("./Resources/larabiefont.ttf");
    m_text.setFont(m_font);
    m_text.setPosition(pos);
    m_text.setString(text);
    m_text.setFillColor(sf::Color::White);
}

Label::Label(sf::Vector2f pos, std::string text, std::function<void(Label*)> updateFunction) :
        Label(std::move(pos),std::move(text)) {
    m_updateFunction = std::move(updateFunction);
}

void Label::draw(sf::RenderWindow &window) {
    window.draw(m_text);
}

void Label::update(double delta) {
    if(m_updateFunction)
        m_updateFunction(this);
}

void Label::setText(std::string s) {
    m_text.setString(s);
}

void Label::setPosition(sf::Vector2f pos) {
    m_text.setPosition(pos);
}

