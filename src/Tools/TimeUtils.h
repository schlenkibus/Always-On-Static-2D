#pragma once
#include <SFML/System.hpp>


namespace TimeUtils {
    static sf::Clock clock;

    static double getDeltaTime() {
        auto curr = clock.getElapsedTime();
        clock.restart();
        return curr.asMicroseconds();
    }

    namespace Physics {
        static sf::Clock clock;

        static bool shouldUpdatePhysics() {
            auto curr = clock.getElapsedTime();
            if(curr.asMilliseconds() >= 1.f/60.f) {
                clock.restart();
                return true;
            }
            return false;
        }
    }

    namespace FPS {

        constexpr const auto max = 200;

        static int tickindex = 0;
        static int ticksum = 0;
        static int ticklist[max] = {0};

        static double getFPS(int newtick) {
            ticksum -= ticklist[tickindex];
            ticksum += newtick;
            ticklist[tickindex] = newtick;
            if (++tickindex == max)
                tickindex = 0;

            return ((double) ticksum / max);
        }

        static int getFPS() {
            return getFPS(getDeltaTime());
        }
    }
};
