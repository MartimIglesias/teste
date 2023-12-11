#include "..\..\headers\servernetwork.hpp"

#define logl(x) std::cout << x << std::endl
#define log(x) std::cout << x

const char *_EVERYONE_RECEIVES_EVENT_IDENTIFIER_ = "-1";

AANetwork::ServerNetwork::ServerNetwork(unsigned short port) 
        : listener(), 
          client_array(),
          client_count(0),
          ids(),
          check_cons(true),
          listen_port(port),
          GE()
{
     logl("Chat Server Started");

     if (listener.listen(listen_port) != sf::Socket::Done)
     {
          logl("Could not listen");
     }
}

int AANetwork::ServerNetwork::getClientCount()
{
    return client_array.size();
}

void AANetwork::ServerNetwork::setCheckCons(bool b)
{
     this->check_cons = b;
}

bool AANetwork::ServerNetwork::getCheckCons()
{
     return this->check_cons;
}

size_t AANetwork::ServerNetwork::getClientPos(std::string id)
{
     for (size_t iterator = 0; iterator < ids.size(); iterator++)
     {
          if(id.compare(ids[iterator]) == 0) return iterator;
     }
     
     return -1;
}

void AANetwork::ServerNetwork::ConnectClients(AANetwork::ThreadSafeVector<sf::TcpSocket *> *client_array)
{
     while (this->check_cons == true)
     {
          sf::TcpSocket *new_client = new sf::TcpSocket();
          if (listener.accept(*new_client) == sf::Socket::Done)
          {
               new_client->setBlocking(false);
               std::cout << "port:" << new_client->getRemotePort() << "\n";
               client_array->push_back(new_client);
               client_count++;

               ids.push_back(std::to_string(client_count));
               
               std::string name = std::to_string(client_count);
               GE.AddPlayer(name);

               logl("Added client " << new_client->getRemoteAddress() << ":" << new_client->getRemotePort() << " on slot " << client_array->size() << " id: " << client_count);
          }
          else
          {
               logl("Server listener error, restart the server");
               delete (new_client);
               break;
          }

          if(client_array->size() >= _MINIMUM_PLAYER_COUNT_)
          {
               this->check_cons = false;
               this->GE.setGameRunning(true);
               this->GE.setGamePhase(AAGame::gamePhases::_DAY_);
               logl("Server Full!");
          }

          std::this_thread::sleep_for((std::chrono::milliseconds)_RESPONSE_WAIT_TIME_); 
     }
}

void AANetwork::ServerNetwork::DisconnectClient(sf::TcpSocket *socket_pointer, size_t position)
{    
     socket_pointer->disconnect();
     
     delete (socket_pointer);
     client_array.erase(client_array.begin() + position);

     GE.RemovePlayerPos(position);
     ids.erase(ids.begin() + position);
     client_count--;

     logl("Client " << socket_pointer->getRemoteAddress() << ":" << socket_pointer->getRemotePort() << " disconnected, removed!");
}

void AANetwork::ServerNetwork::BroadcastPacket(sf::Packet &packet, sf::IpAddress exclude_address, unsigned short port)
{
     for (size_t iterator = 0; iterator < client_array.size(); iterator++)
     {
          sf::TcpSocket *client = client_array[iterator];
          if (client->getRemoteAddress() != exclude_address || client->getRemotePort() != port)
          {
               if (client->send(packet) != sf::Socket::Done)
               {
                    logl("Could not send packet on broadcast");
               }
          }
     }
}

void AANetwork::ServerNetwork::BroadcastEvent(AAGame::Event ev, sf::IpAddress addr, unsigned short port)
{
    std::string ev_string = ev.EventToString();

    sf::Packet broad_packet;
    broad_packet << ev_string;

    this->BroadcastPacket(broad_packet, sf::IpAddress::None, 0);
}

void AANetwork::ServerNetwork::SendEventToClient(AAGame::Event ev, sf::IpAddress addr, unsigned short port)
{
     std::string ev_string = ev.EventToString();
     sf::Packet packet;
     packet << ev_string;

     for (size_t iterator = 0; iterator < client_array.size(); iterator++)
     {
          sf::TcpSocket *client = client_array[iterator];
          if (client->getRemoteAddress() == addr && client->getRemotePort() == port)
          {
               if (client->send(packet) != sf::Socket::Done)
               {
                    logl("Could not send packet on broadcast");
               }
          }
     }
}

AAGame::Event AANetwork::ServerNetwork::SendPacketToGameEngine(sf::Packet &packet, size_t iterator)
{
     return this->GE.ManageEvents(iterator, packet);
}

AAGame::Event AANetwork::ServerNetwork::ReceivePacket(sf::TcpSocket *client, size_t iterator)
{
     sf::Packet packet;
     AAGame::Event response_ev;

     if (client->receive(packet) == sf::Socket::Disconnected) DisconnectClient(client, iterator);
     else if (packet.getDataSize() > 0)
     {
          std::string received_message;
          packet >> received_message;

          packet.clear(); //?

          packet << received_message << client->getRemoteAddress().toString() << client->getRemotePort();

          response_ev = SendPacketToGameEngine(packet, iterator);
          logl(client->getRemoteAddress().toString() << ":" << client->getRemotePort() << " '" << received_message << "'");
     }

     return response_ev;
}

void AANetwork::ServerNetwork::SendEvent(AAGame::Event ev)
{
     if (ev.getReceiverName().compare(_EVERYONE_RECEIVES_EVENT_IDENTIFIER_) == 0)
     {
          BroadcastEvent(ev, sf::IpAddress::None, 0);
     }
     else
     {
          std::cout << "SMOASMNDMNAO" << "\n";
          size_t pos = this->getClientPos(ev.getReceiverName());
          if (pos != -1)
          {
               std::cout << pos << "\n";
               sf::IpAddress addr = client_array[pos]->getRemoteAddress();
               int port_number = client_array[pos]->getRemotePort();
               SendEventToClient(ev, addr, port_number);
          }
     }
}

void AANetwork::ServerNetwork::ManagePackets()
{
     while (true)
     {
          if(this->GE.getEventListSize() > 0)
          {
               for (int i = 0; i < this->GE.getEventListSize(); i++)
               {
                    AAGame::Event ev = this->GE.popFirstEventListElement();
                    std::cout << ev.EventToString() << "\n";
                    SendEvent(ev);
               }
          }
          else
          {
               for (size_t iterator = 0; iterator < client_array.size(); iterator++)
               {
                    AAGame::Event response_ev = ReceivePacket(client_array[iterator], iterator);
                    if (response_ev.isEmpty() == false) SendEvent(response_ev);
               }
          }

          std::this_thread::sleep_for((std::chrono::milliseconds)_RESPONSE_WAIT_TIME_);
     }
}

void AANetwork::ServerNetwork::Run()
{
     std::thread connetion_thread(&ServerNetwork::ConnectClients, this, &client_array);
     std::thread flow_thread(&ServerNetwork::ManagePackets, this);

     this->GE.Run();

     connetion_thread.join();
     flow_thread.join();
}
