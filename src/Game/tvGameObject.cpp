#include "tvGameObject.h"


tvGameObject::tvGameObject(sf::Texture &tex, sf::Vector2f pos, std::function<void(void)> callback) : m_callBack(callback) {
    m_texture = tex;
    m_sprite.setPosition(pos);
    m_sprite.setTexture(m_texture);
}

void tvGameObject::draw(sf::RenderWindow& window) {
    window.draw(m_sprite);
}

void tvGameObject::update(double delta) {
    if(m_callBack) {
        m_callBack();
    }
}

sf::Sprite& tvGameObject::getSprite() {
    return m_sprite;
}