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

    namespace Logic {
        static sf::Clock symbolClock;
        static sf::Clock jumpClock;

        static bool isThresholdExeeded() {
            auto curr = symbolClock.getElapsedTime();
            if(curr.asSeconds() >= 5) {
                symbolClock.restart();
                return true;
            }
            return false;
        }

        static void resetSymbolClock() {
            symbolClock.restart();
        }

        static bool canJump() {
            auto curr = jumpClock.getElapsedTime();
            if(curr.asSeconds() >= 0.5) {
                jumpClock.restart();
                return true;
            }
            return false;
        }
    }

    namespace Drawing {
        static sf::Clock clock;
        static sf::Clock symbolClock;

        static bool shouldRedrawScatter() {
            auto curr = clock.getElapsedTime();
            if(curr.asMilliseconds() >= 150) {
                clock.restart();
                return true;
            }
            return false;
        }

        static bool shouldMoveSymbol() {
            auto curr = symbolClock.getElapsedTime();
            if(curr.asSeconds() >= 0.016) {
                symbolClock.restart();
                return true;
            }
            return false;
        }

        static sf::Clock hideClock;

        static bool shouldHideSymbol() {
            auto curr = hideClock.getElapsedTime();
            if(curr.asSeconds() >= 2) {
                hideClock.restart();
                return true;
            }
            return false;
        }
    }

    namespace Network {
        static sf::Clock clock;

        static bool shouldSendSymbol() {
            auto curr = clock.getElapsedTime();
            if(curr.asMilliseconds() >= 300) {
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
