#pragma once
#include "GameState.h"
#include <memory>
#include "../Application.h"
#include "../GUI/Label.h"

class CreditScreen :
	public GameState
{
public:
	CreditScreen();
	~CreditScreen();
	void update(double deltaTime) override;
	void draw(sf::RenderWindow& window) override;
	void onMessageRecieved(std::string message) override;
protected:
	std::vector<std::unique_ptr<sf::Sprite>> m_sprites;
	std::vector<std::unique_ptr<Label>> m_label;
};

