#pragma once

#include "Label.h"

class TextInput : public Label {
public:
    TextInput(sf::Vector2f pos);
    ~TextInput() = default;
    bool textEntered(sf::Event &event) override;
    void commit(std::string &string);
protected:

};
