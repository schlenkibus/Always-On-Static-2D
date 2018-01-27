#pragma once
#include <SFML/Graphics.hpp>


namespace createNoiseImage {

    sf::Color calculateTransmissionPixelColor() {
        sf::Uint8 grey = (rand() % 10) + 100;
        sf::Uint8 white = (rand() % 10) + 245;
        sf::Uint8 black = (rand() % 10);
        sf::Uint8 alpha = 250;
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

    sf::Image calculateTransmissionPicture() {
        sf::Image img;
        img.create(500, 300);
        for(auto y = 0; y < img.getSize().y; y++) {
            for(auto x = 0; x < img.getSize().x; x++) {
                img.setPixel(x, y, calculateTransmissionPixelColor());
            }
        }
        return img;
    }

    void exportNoise(int count) {
        for(int i = 0; i < count; i++) {
            calculateTransmissionPicture().saveToFile("Resources/noise/" + std::to_string(i) + ".png");
        }
    }
};