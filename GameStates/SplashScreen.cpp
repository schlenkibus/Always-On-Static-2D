#include "SplashScreen.h"
#include "MenuGameState.h"

SplashScreen::SplashScreen()
{

	m_label.push_back(std::make_unique<Label>(sf::Vector2f(400, 250), "Always On Static"));
	m_label.back()->getTextObject().setCharacterSize(40);
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(500, 300), "Powered by:"));
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(500, 340), "C++"));
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(500, 380), "SFML"));
	m_label.push_back(std::make_unique<Label>(sf::Vector2f(0, 300), "Made during:"));
	m_sprites.push_back(std::make_unique<sf::Sprite>());
	m_sprites.back()->setTexture(Application::get().getResourceManager().getTexture("GGJLogo.png"));
	m_sprites.back()->setPosition(sf::Vector2f(0, 330));
}




SplashScreen::~SplashScreen()
{
}

void SplashScreen::draw(sf::RenderWindow& window) {
	for (auto& l : m_label)
		l->draw(window);

	for (auto& s : m_sprites)
		window.draw(*s.get());
}

void SplashScreen::onMessageRecieved(std::string message) {

}

void SplashScreen::update(double deltaTime) {
	for (auto& l : m_label)
		l->update(deltaTime);

	if (timeout.getElapsedTime().asSeconds() > 4.0)
		Application::get().installState(std::make_unique<MenuGameState>());
};