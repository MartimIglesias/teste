#include "..\..\headers\clientnetwork.hpp"
#include "SFML\System\String.hpp"

//CHANGE!!
AANetwork::ClientNetwork::ClientNetwork(const char *address, unsigned short port)
     :    socket(),
          user(),
          isConnected(false)
{
     this->Connect(address, port);
     this->Run();
     loggl("Chat Client Started");
}

void AANetwork::ClientNetwork::Connect(const char *address, unsigned short port)
{
     if (socket.connect(address, port) != sf::Socket::Done)
     {
          loggl("Could not connect to the server\n");
     }
     else
     {
          this->isConnected = true;
          loggl("Connected to the server\n");
     }
}

sf::Packet AANetwork::ClientNetwork::ReceivePacket(sf::TcpSocket *socket)
{
     sf::Packet pckt;
     sf::Packet response_pckt;
     if (socket->receive(pckt) == sf::Socket::Done)
     {    
          if(pckt.getDataSize() > 0)
          {
               std::string received_message;
               pckt >> received_message;
               loggl(received_message);
               AAGame::Event response_ev = this->user.ManageEvents(pckt);
               if(response_ev.getType() != AAGame::Event::EventType::DEFAULT)
               {
                    std::string response_string = response_ev.EventToString();
                    response_pckt << response_string;
               }
          }
     }
     else loggl("Could not receive packet");

     return response_pckt;
}

void AANetwork::ClientNetwork::SendPacket(sf::Packet &packet)
{
     if (packet.getDataSize() > 0 && socket.send(packet) != sf::Socket::Done)
     {
          loggl("Could not send packet");
     }
}

void AANetwork::ClientNetwork::ManagePackets()
{
     while(true)
     {
          if(this->user.getEventListSize() > 0)
          {
               for (int i = 0; i < this->user.getEventListSize(); i++)
               {
                    std::string s = this->user.popFirstEventListElement().EventToString();
                    sf::Packet p;
                    p << s;
                    SendPacket(p);
               }
          }
          else
          {
          sf::Packet response_pckt = ReceivePacket(&socket);
          if(response_pckt.getDataSize() > 0) SendPacket(response_pckt);
          }

     std::this_thread::sleep_for((std::chrono::milliseconds)_RESPONSE_WAIT_TIME_);
     }
}

void AANetwork::ClientNetwork::SendEvent(AAGame::Event ev)
{
     std::string ev_string = ev.EventToString();

     sf::Packet broad_packet;
     broad_packet << ev_string;

     SendPacket(broad_packet);
}

void AANetwork::ClientNetwork::Run()
{
     std::thread reception_thread(&AANetwork::ClientNetwork::ManagePackets, this);

     reception_thread.join();
}


