#pragma once
#include <string.h>
#include "GameEngine2.hpp"

const int _PORT_NUMBER_ = 2525;
const int _RESPONSE_WAIT_TIME_ = 250;
extern const char* _EVERYONE_RECEIVES_EVENT_IDENTIFIER_;

namespace AANetwork
{
     class ServerNetwork
     {
          sf::TcpListener listener;
          AAGame::GameEngine GE;
          AANetwork::ThreadSafeVector<sf::TcpSocket *> client_array;
          int client_count;
          AANetwork::ThreadSafeVector<std::string> ids;
          bool check_cons;

          unsigned short listen_port;

     public:
          // this "constructor" only checks if the port can be used
          ServerNetwork(unsigned short);

          int getClientCount();
          void setCheckCons(bool);
          bool getCheckCons();
          size_t getClientPos(std::string id);

          // creates the socket to exchange data with client
          void ConnectClients(AANetwork::ThreadSafeVector<sf::TcpSocket *> *);
          // deletes the client
          void DisconnectClient(sf::TcpSocket *, size_t);
          AAGame::Event ReceivePacket(sf::TcpSocket *, size_t);
          // broadcasts packet to every client minus the specified address and port
          void BroadcastPacket(sf::Packet &, sf::IpAddress, unsigned short);  
          void BroadcastEvent(AAGame::Event, sf::IpAddress, unsigned short);
          // sends ONLY to address @ port
          void SendEventToClient(AAGame::Event, sf::IpAddress, unsigned short);
          void SendEvent(AAGame::Event);
          AAGame::Event SendPacketToGameEngine(sf::Packet &, size_t);
          // calls receivePacket in a infinite loop with a delay between iteration
          void ManagePackets();
          // creates a thread and calls ManagePacket
          void Run();
     };
}