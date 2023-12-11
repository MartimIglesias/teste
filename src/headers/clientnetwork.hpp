#pragma once
#include <iostream>
#include <thread>
#include <chrono>
#include "User2.hpp"

#define loggl(x) std::cout << x << std::endl
#define logg(x) std::cout << x

const int _RESPONSE_WAIT_TIME_ = 250;

namespace AANetwork
{
     class ClientNetwork
     {
     protected:
          sf::TcpSocket socket;
          AAGame::User user;

          bool canChat = 0;
          bool isConnected = false;
     public:
          //initializes the client to defaults values and connects it to address 'address' and port number 'port'
          ClientNetwork(const char *, unsigned short);

          void Connect(const char *, unsigned short);
          // updates last_packet
          sf::Packet ReceivePacket(sf::TcpSocket *);
          void SendPacket(sf::Packet &);
          void ManagePackets();
          void SendEvent(AAGame::Event);
          void receiveEvent(AAGame::Event);
          void Run();

     };
} // namespace AANetwork