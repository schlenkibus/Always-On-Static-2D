#pragma once
#include <SFML/System.hpp>
#include "../Application.h"

namespace TimeUtils {

    namespace Physics {
		static long tickcount1 = 0;
		static long tickcount2 = 0;
        static sf::Clock clock;
		static sf::Clock clock2;

        static bool shouldUpdatePhysics() {
                return true;
        }

		static bool shouldUpdatePhysics2() {
			
				return true;
			
		}
    }

    namespace Logic {
        static sf::Clock symbolClock;
        static sf::Clock jumpClock;
		static sf::Clock jumpClock2;

        static bool isThresholdExeeded() {
            auto curr = symbolClock.getElapsedTime();
            if(curr.asSeconds() >= Application::get().getSignalLenght()) {
				Application::get().shortenSignalLenght();
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
			if (curr.asSeconds() >= 0.5) {
				jumpClock.restart();
				return true;
			}
			return false;
		}

		static bool canJump2() {
			auto curr = jumpClock2.getElapsedTime();
			if (curr.asSeconds() >= 0.1) {
				jumpClock2.restart();
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

		static sf::Clock funClock;

		static bool shouldMakeFun() {
			auto curr = funClock.getElapsedTime();
			if (curr.asSeconds() >= 0.15) {
				funClock.restart();
				return true;
			}
			return false;
		}

		static sf::Clock funClock2;

		static bool shouldMakeFun2() {
			auto curr = funClock2.getElapsedTime();
			if (curr.asSeconds() >= 0.15) {
				funClock2.restart();
				return true;
			}
			return false;
		}

		static sf::Clock funClock3;

		static bool shouldMakeFun3() {
			auto curr = funClock3.getElapsedTime();
			if (curr.asSeconds() >= 0.15) {
				funClock3.restart();
				return true;
			}
			return false;
		}

		static sf::Clock funClock4;

		static bool shouldMakeFun4() {
			auto curr = funClock4.getElapsedTime();
			if (curr.asSeconds() >= 0.15) {
				funClock4.restart();
				return true;
			}
			return false;
		}

		static sf::Clock funClock5;

		static bool shouldMakeFun5() {
			auto curr = funClock5.getElapsedTime();
			if (curr.asSeconds() >= 0.15) {
				funClock5.restart();
				return true;
			}
			return false;
		}

		static sf::Clock funClock6;

		static bool shouldMakeFun6() {
			auto curr = funClock6.getElapsedTime();
			if (curr.asSeconds() >= 0.15) {
				funClock6.restart();
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

        static sf::Clock oclock;
        static bool shouldSendOther() {
            auto curr = oclock.getElapsedTime();
            if(curr.asMilliseconds() >= 70) {
                oclock.restart();
                return true;
            }
            return false;
        }
    }
};
