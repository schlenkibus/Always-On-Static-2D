#include "CreditScreen.h"
#include "MenuGameState.h"
#include "../Tools/TimeUtils.h"

CreditScreen::CreditScreen()
{

	m_label.push_back(std::make_unique<Label>(sf::Vector2f(400, 0), "Always On Static: Team:", [](Label* l) {
		if (TimeUtils::Drawing::shouldMakeFun()) {
			if(l->getTextObject().getColor() == sf::Color::Magenta)
				l->getTextObject().setColor(sf::Color::Cyan);
			else
				l->getTextObject().setColor(sf::Color::Magenta);
		}
	}));
	m_label.back()->getTextObject().setCharacterSize(40);
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(932, 644), "Justus Scheil\n(Programming, Music)", [](Label* l) {
		if (TimeUtils::Drawing::shouldMakeFun2()) {
			if (l->getTextObject().getColor() == sf::Color::Green)
				l->getTextObject().setColor(sf::Color::Magenta);
			else
				l->getTextObject().setColor(sf::Color::Green);
		}
	}));
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(761, 552), "Georg Marth\n(Programming)", [](Label* l) {
		if (TimeUtils::Drawing::shouldMakeFun3()) {
			if (l->getTextObject().getColor() == sf::Color::Red)
				l->getTextObject().setColor(sf::Color::Green);
			else
				l->getTextObject().setColor(sf::Color::Red);
		}
	}));
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(164, 371), "Felix Szczesny\n(2D Art and Animation)", [](Label* l) {
		if (TimeUtils::Drawing::shouldMakeFun4()) {
			if (l->getTextObject().getColor() == sf::Color::Yellow)
				l->getTextObject().setColor(sf::Color::Blue);
			else
				l->getTextObject().setColor(sf::Color::Yellow);
		}
	}));
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(473, 590), "Erik Nuernberg\n(3D Art)", [](Label* l) {
		if (TimeUtils::Drawing::shouldMakeFun5()) {
			if (l->getTextObject().getColor() == sf::Color::White)
				l->getTextObject().setColor(sf::Color(157,200,66));
			else
				l->getTextObject().setColor(sf::Color::White);
		}
	}));
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(400, 50), "Made during GGJ 2018 @ SAE Berlin", [](Label* l) {
		if (TimeUtils::Drawing::shouldMakeFun6()) {
			if (l->getTextObject().getColor() == sf::Color::Magenta)
				l->getTextObject().setColor(sf::Color::Green);
			else
				l->getTextObject().setColor(sf::Color::Magenta);
		}
	}));
	m_sprites.push_back(std::make_unique<sf::Sprite>());
	m_sprites.back()->setTexture(Application::get().getResourceManager().getTexture("credits.png"));
	m_sprites.back()->setPosition(sf::Vector2f(0, 0));
}




CreditScreen::~CreditScreen()
{
}

void CreditScreen::draw(sf::RenderWindow& window) {
	for (auto& s : m_sprites)
		window.draw(*s.get());
	
	for (auto& l : m_label)
		l->draw(window);


}

void CreditScreen::onMessageRecieved(std::string message) {

}

void CreditScreen::update(double deltaTime) {
	for (auto& l : m_label)
		l->update(deltaTime);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		Application::get().installState(std::make_unique<MenuGameState>());
};