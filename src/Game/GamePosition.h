
#include <SFML/System/Vector2.hpp>
#include <Box2D/Common/b2Math.h>
#include "../Application.h"

struct GamePosition {
    GamePosition(sf::Vector2f pos) : x{pos.x}, y{pos.y} {
    }
    GamePosition(b2Vec2 pos) {
        y = Application::get().getWindowSize().y - pos.y;
        x = pos.x;
    }

    sf::Vector2f getAsSFML() {
        return sf::Vector2f(x,y);
    }

    b2Vec2 getAsBox2D() {
        auto yy = Application::get().getWindowSize().y - y;
        return b2Vec2(x, yy);
    }

    float x, y;
};