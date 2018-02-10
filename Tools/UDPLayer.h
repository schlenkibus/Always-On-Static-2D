#pragma once
#include <SFML/Network.hpp>
#include <chrono>
#include <iostream>
#include "../Application.h"

class UDPLayer {
public:
    UDPLayer() {

    }

    static void run() {
        while(Application::get().getGameState() == "g:m")
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }


        sf::UdpSocket socketSend;
        sf::UdpSocket socketRec;
        socketRec.bind(22222);
        socketRec.setBlocking(false);

        socketSend.bind(55555);

        char buffer[1024];
        std::size_t received = 0;
        sf::IpAddress sender;
        unsigned short port;


        while(Application::get().getWindow().isOpen()) {
			auto ip = Application::get().getIpAdress();

            if(TimeUtils::Network::shouldSendSymbol()) {

                auto symbolChar = Application::get().getCurrentGameSymbol();
                if (symbolChar != "") {
                    socketSend.send(std::string(symbolChar).c_str(), sizeof(symbolChar), ip, 55557);
					std::cout << "send symbol: " << symbolChar << '\n';
                }
            }
			

			auto currGameState = Application::get().getGameState();
			if (currGameState != "g:p") {
				socketSend.send(currGameState.c_str(), sizeof(currGameState), ip, 55557);
				std::cout << "send gamestate!\n";
			}

			auto message = Application::get().getMessageToSend();
			if (message != "") {
				socketSend.send(message.c_str(), sizeof(message), ip, 55557);
				std::cout << "send message: " << message << '\n';
			}

            if (socketRec.receive(buffer, sizeof(buffer), received, sender, port) == sf::Socket::Done) {
                std::string message;
                for(int i = 0; i < received; i++)
                    message += buffer[i];

				std::cout << "recieved: " << message << '\n';

                Application::get().onMessageRecieved(message);

                received = 0;
            }
        }
    }
};