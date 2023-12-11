#include "..\headers\servernetwork.hpp"

int main()
{
    AANetwork::ServerNetwork server(2525);
    server.Run();

}