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
    void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
    std::string getText();
    virtual bool textEntered(sf::Event& event) {return false;};
	void setColor(sf::Color c) {
		m_text.setColor(c);
	};

	sf::Text& getTextObject() {
		return m_text;
	}
private:
    sf::Text m_text;
    sf::Font m_font;
    std::function<void(Label*)> m_updateFunction;
};
