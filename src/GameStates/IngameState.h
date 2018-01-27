#pragma once

#include "GameState.h"
#include "../GUI/Label.h"
#include "../Box2D/PhysicsWorld.h"

class IngameState : public GameState {

protected:
    enum symbols {
        x,y,z
    };
public:
    IngameState();
    ~IngameState();
    void update(double deltaTime) override;
    void draw(sf::RenderWindow &window) override;
    void onMessageRecieved(std::string message) override;
    int getTransmissionRate();
    const char* getSymbol();
private:

    sf::Image calculateTransmissionPicture();
    sf::Color calculateTransmissionPixelColor();


    std::vector<std::unique_ptr<Label>> m_labels;
    std::unique_ptr<PhysicsWorld> m_world;
    std::vector<sf::Image> m_transmissionImages;

    sf::Image m_screenOverlayImage;
    sf::Texture m_screenTexture;
    sf::Sprite m_screenSprite;


    symbols m_currentCorrectSymbol;
    int m_transmissionRate;
};
