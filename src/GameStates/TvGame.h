#pragma once

#include "../Box2D/PhysicsWorld.h"
#include "../GUI/Label.h"
#include "../Game/tvGameObject.h"

class TvGame {
public:
    TvGame(PhysicsWorld* parent);
    void update(double delta);
    void draw(sf::RenderWindow& window);

    bool isGameOver();
    int getLifes();
protected:
    void installGameOver();
    std::vector<std::unique_ptr<tvGameObject>> m_obstacles;
    PhysicsWorld* m_parent;
    std::unique_ptr<Label> m_label;
    bool m_gameOver = false;
    double m_speed = -0.5;
    short m_lifes = 3;
};
