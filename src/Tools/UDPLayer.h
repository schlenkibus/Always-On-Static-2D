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
        std::string ip("10.3.35.173");
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

            if(TimeUtils::Network::shouldSendSymbol()) {
                std::string symbol = Application::get().getCurrentGameSymbol();
                socketSend.send(symbol.c_str(), sizeof(symbol), ip, 55557);
            }

            if (socketRec.receive(buffer, sizeof(buffer), received, sender, port) == sf::Socket::Done) {
                std::string message;
                for(int i = 0; i < received; i++)
                    message += buffer[i];

                Application::get().onMessageRecieved(message);
                std::cout << buffer << '\n';
            }
        }
    }
};