#pragma once

#include "../Box2D/PhysicsWorld.h"
#include "../GUI/Label.h"
#include "../Game/tvGameObject.h"

class genericGameObject;

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
    std::vector<std::unique_ptr<genericGameObject>> m_floor;
    PhysicsWorld* m_parent;
    std::vector<std::unique_ptr<Label>> m_label;
    bool m_gameOver = false;
    double m_speed = -5;
    short m_lifes = 5;
    bool m_tookDamage = false;
    int m_score = 0;
};
