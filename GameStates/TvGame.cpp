//
// Created by justus on 27.01.18.
//

#include <iostream>
#include "TvGame.h"
#include "../Tools/TimeUtils.h"
#include "IngameState.h"
#include "../Game/genericGameObject.h"

TvGame::TvGame(PhysicsWorld *parent) : m_parent(parent) {

    m_label.push_back(std::make_unique<Label>(sf::Vector2f(390, 90), "Lifes: ", [this](Label* l){
        if(isGameOver()) {
            l->setPosition(sf::Vector2f(585, 239));
            l->setText("Game Over!");
        }
        else {
            l->setText(std::string("Lifes: ") + std::to_string(getLifes()));
        }
    }));

    m_label.push_back(std::make_unique<Label>(sf::Vector2f(390, 111), "Score: ", [this](Label* l){
        if(isGameOver()) {
            l->setPosition(sf::Vector2f(585, 269));
            l->setText("Final Score: " + std::to_string(getScore()));
        }
        else {
            l->setText(std::string("Score: ") + std::to_string(getScore()));
        }
    }));

	m_obstacle = std::make_unique<tvGameObject>(Application::get().getResourceManager().getTexture("tv/cacti.png"), sf::Vector2f(1100, 293), nullptr);
	m_obstacle->getSprite().setScale(0.8, 0.8);
	m_obstacle->getSprite().move(0, m_obstacle->getSprite().getTextureRect().height * 0.2);

    parent->addActor<GameActor>(std::make_unique<GameActor>(*parent, Application::get().getResourceManager().getTexture("tv/ground.png"), sf::Vector2f(363, 470), std::string("ground"), true));
    parent->getActor("ground")->getSprite().setColor(sf::Color(0,0,0,0));
    parent->addActor<PlayerActor>(std::make_unique<PlayerActor>(*parent, Application::get().getResourceManager().getTexture("tv/dino/dino1.png"), sf::Vector2f(440, 317), std::string("dino")));
    parent->getActor("dino")->getBody()->SetGravityScale(6);

    m_floor.push_back(std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("/tv/ground.png")));
    m_floor.back()->setPosition(sf::Vector2f(1800, 371));
    m_floor.push_back(std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("/tv/ground.png")));
    m_floor.back()->setPosition(sf::Vector2f(1000, 371));
    m_floor.push_back(std::make_unique<genericGameObject>(Application::get().getIngameGameState(), Application::get().getResourceManager().getTexture("/tv/ground.png")));
    m_floor.back()->setPosition(sf::Vector2f(200, 371));

}

int TvGame::getScore() {
    return m_score;
}

void TvGame::update(double delta) {

	for (auto& l : m_label) {
		l->update(delta);
	}

    if(Application::get().getGameState() != "g:p")
        return;
	
    auto playerActor = dynamic_cast<PlayerActor*>(m_parent->getActor("dino").get());
    

    if(!m_gameOver) {

        if(TimeUtils::Physics::shouldUpdatePhysics()) {
        
			playerActor->update(delta);
			
			m_obstacle->getSprite().move(sf::Vector2f(m_speed, 0));
            for(auto& f: m_floor){
                f->getSprite().move(sf::Vector2f(m_speed, 0));
            }
			for (auto& f : m_floor) {
				if (f->getSprite().getGlobalBounds().left < -500) {
					f->getSprite().move(1600, 0);
				}
			}
        }


		auto obstacleSmaller = m_obstacle->getSprite().getGlobalBounds();
		obstacleSmaller.height = obstacleSmaller.height * 0.75;
		obstacleSmaller.top = obstacleSmaller.top + obstacleSmaller.height * 0.25;
		obstacleSmaller.width = obstacleSmaller.width * 0.5;

        if(!m_tookDamage &&
           playerActor->getSprite().getGlobalBounds().intersects(obstacleSmaller))
        {
            playerActor->getDamage();
            m_lifes--;
            m_tookDamage = true;
            if (m_lifes == 0) {
                m_gameOver = true;
                installGameOver();
            }
        }



        if(m_obstacle->getSprite().getGlobalBounds().left < 330) {
            playerActor->stopDamage();
            if(!m_tookDamage)
                m_score++;
			int posx = 1100 + rand() % 300;
            m_obstacle->getSprite().setPosition(posx, 293);
			m_obstacle->getSprite().move(0, m_obstacle->getSprite().getTextureRect().height * 0.2 + 2);
            m_tookDamage = false;
        }
	}
}

void TvGame::installGameOver() {
    Application::get().setGameState("g:o");
}

void TvGame::draw(sf::RenderWindow& window) {
    m_obstacle->draw(window);

    for(auto& f: m_floor)
        f->draw(window);

    for(auto& l: m_label)
        l->draw(window);
}

bool TvGame::isGameOver() {
    return m_gameOver;
}

int TvGame::getLifes() {
    return m_lifes;
}

