//
// Created by justus on 27.01.18.
//

#include "TextInput.h"
#include "../Application.h"

TextInput::TextInput(sf::Vector2f pos) : Label{pos, "10.3.35.173"} { //
    Application::get().setIp(getText());
}

bool TextInput::textEntered(sf::Event &event)
{
    if (event.type == sf::Event::TextEntered)
    {
        auto string = getText();
        if(event.text.unicode == '\b')
        {
            if(!string.empty())
            {
                string.erase(string.size() - 1, 1);
                commit(string);
            }
        }
        else if (event.text.unicode < 128)
        {
            string += static_cast<char>(event.text.unicode);
            commit(string);
        }
        return true;

    }
    return false;
}

void TextInput::commit(std::string &string)
{
    setText(string);
    Application::get().setIp(string);
}