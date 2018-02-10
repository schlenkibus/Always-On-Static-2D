#pragma once

#include "Label.h"

class TextInput : public Label {
public:
    TextInput(sf::Vector2f pos);
    ~TextInput();
    bool textEntered(sf::Event &event) override;
	void commit(std::string &string);
};
