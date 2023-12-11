#include "..\headers\NetworkManager.hpp"

AANetwork::NetworkManager::NetworkManager()
    : server(-1),
      Users()
{}

AANetwork::NetworkManager::NetworkManager(unsigned short port)
    : server(port),
      Users()
{
  server.Run();
}
