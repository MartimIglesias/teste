#include "..\..\headers\chatnetwork.hpp"

AANetwork::Chat::Chat()
{
    loggl("Chat Client Started");
}

void AANetwork::Chat::Run()
{
    std::thread reception_thread(&AANetwork::Chat::ReceivePacket, this, &socket);
    

    while (true)
    {
        if (isConnected)
        {
            std::string user_input;
            std::getline(std::cin, user_input);

            if (user_input.length() < 1)
                continue;

            sf::Packet reply_packet;
            reply_packet << user_input;

            SendPacket(reply_packet);
        }
    }

    if (reception_thread.joinable()) {
          reception_thread.join();
    }
}