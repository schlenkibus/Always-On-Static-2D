#pragma once

#include "gameObject.h"

class currentSymbolObject : public gameObject {
public:
    currentSymbolObject(IngameState* parent);
    void update(double delta) override;
    void draw(sf::RenderWindow& window) override;
protected:
    std::string m_currsymbol;
    bool moving;
};
