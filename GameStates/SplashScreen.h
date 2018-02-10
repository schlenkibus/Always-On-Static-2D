#pragma once
#include "GameState.h"
#include <memory>
#include "../Application.h"
#include "../GUI/Label.h"

class SplashScreen :
	public GameState
{
public:
	SplashScreen();
	~SplashScreen();
	void update(double deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void onMessageRecieved(std::string message) override;
protected:
	sf::Clock timeout;
	std::vector<std::unique_ptr<sf::Sprite>> m_sprites;
	std::vector<std::unique_ptr<Label>> m_label;
};

