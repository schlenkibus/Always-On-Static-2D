#include "Button.h"
#include "../Application.h"

Button::Button(std::function<void(void)> callback, std::string text, sf::Texture& texture, sf::Vector2f pos) :
        m_callback{std::move(callback)},
        m_label{pos, std::move(text)} {
    m_sprite.setPosition(pos);
    m_sprite.setTexture(texture);
}

void Button::update(double deltaTime) {
    m_label.update(deltaTime);

    if(isHovered())
        m_sprite.setScale(1.01, 1.01);
    else
        m_sprite.setScale(1, 1);

    if(isClicked())
        m_callback();
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
    m_label.draw(window);
}

bool Button::isClicked() {
    return isHovered() && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

bool Button::isHovered() {
    auto& app = Application::get();
    auto pos = sf::Mouse::getPosition(app.getWindow());
    return m_sprite.getGlobalBounds().contains(pos.x, pos.y);
}