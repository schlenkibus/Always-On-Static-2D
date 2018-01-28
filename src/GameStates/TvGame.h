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
    int getScore();
protected:
    void installGameOver();
    std::unique_ptr<tvGameObject> m_obstacle;
    PhysicsWorld* m_parent;
    std::vector<std::unique_ptr<Label>> m_label;
    bool m_gameOver = false;
    double m_speed = -0.0003;
    short m_lifes = 50;
    bool m_tookDamage = false;
    int m_score = 0;
};
