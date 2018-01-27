#include <iostream>
#include "IngameState.h"
#include "../Tools/TimeUtils.h"

IngameState::IngameState() : GameState(), m_transmissionRate(100), m_currentCorrectSymbol{symbols::x} {
    m_world = std::make_unique<PhysicsWorld>();

    m_labels.push_back(std::make_unique<Label>(sf::Vector2f(0, 50), "rate: ", [this](Label* l){
        l->setText(std::string("rate: ") + std::to_string(getTransmissionRate()));
    }));


    for(int i = 0; i < 20; i++) {
        m_transmissionImages.push_back(calculateTransmissionPicture());
    }
    m_screenOverlayImage = m_transmissionImages.back();

    m_screenTexture.loadFromImage(m_screenOverlayImage);
    m_screenSprite.setTexture(m_screenTexture);
    m_screenSprite.setPosition(100, 100);

   /* m_world->addActor(std::make_shared<GameActor>(*m_world.get(), Application::get().getResourceManager().getTexture("floor.png"),
                                                   sf::Vector2f(0, 700), std::string("floor"), true));

    m_world->addActor(std::make_shared<PlayerActor>(*m_world.get(), Application::get().getResourceManager().getTexture("player.png"),
                                                   sf::Vector2f(100, 200), std::string("player")));

    */
}

IngameState::~IngameState() {

}

void IngameState::onMessageRecieved(std::string message) {
    m_transmissionRate = atoi(message.c_str());
}

void IngameState::update(double deltaTime) {
    m_world->update(deltaTime);

    m_screenSprite.setColor(sf::Color(255, 255, 255, m_transmissionRate * 2.55));

    auto mousepos = sf::Mouse::getPosition(Application::get().getWindow());

    if(m_screenSprite.getGlobalBounds().contains(mousepos.x, mousepos.y) && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        m_transmissionRate = rand() % 100;
    }

    if(TimeUtils::Drawing::shouldRedrawScatter()) {
        m_screenOverlayImage = m_transmissionImages[rand() % 20];
        m_screenTexture.loadFromImage(m_screenOverlayImage);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
        m_currentCorrectSymbol = symbols::x;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
        m_currentCorrectSymbol = symbols::y;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        m_currentCorrectSymbol = symbols::z;
    }

    if(TimeUtils::Physics::shouldUpdatePhysics())
        m_world->updatePhysics();


    for(auto& l: m_labels) {
        l->update(deltaTime);
    }
}



const char* IngameState::getSymbol() {
    switch(m_currentCorrectSymbol) {
        case symbols::x:
            return "s:x";
        case symbols::y:
            return "s:y";
        case symbols::z:
            return "s:z";
        default:
            return "NAN";
    }
}

void IngameState::draw(sf::RenderWindow &window) {
    m_world->draw(window);

    window.draw(m_screenSprite);

    for(auto& l: m_labels) {
        l->draw(window);
    }
}

int IngameState::getTransmissionRate() {
    return m_transmissionRate;
}


sf::Image IngameState::calculateTransmissionPicture() {
    sf::Image img;
    img.create(300, 300);
    for(auto y = 0; y < img.getSize().y; y++) {
        for(auto x = 0; x < img.getSize().x; x++) {
            img.setPixel(x, y, calculateTransmissionPixelColor());
        }
    }
    return img;
}

sf::Color IngameState::calculateTransmissionPixelColor() {
    sf::Uint8 grey = (rand() % 10) + 100;
    sf::Uint8 white = (rand() % 10) + 245;
    sf::Uint8 black = (rand() % 10);
    sf::Uint8 alpha = (rand() % 100) + 100;
    auto what = rand() % 3;
    sf::Color c;
    c.a = alpha;
    switch(what) {
        case 0:
            c.r = grey;
            c.g = grey;
            c.b = grey;
            break;
        case 1:
            c.r = white;
            c.g = white;
            c.b = white;
            break;
        case 2:
            c.r = black;
            c.g = black;
            c.b = black;
            break;

    }
    return c;
}