// Chat Server
#include "..\..\headers\servernetwork.hpp"

int main(int argc, char *argv[])
{
     AANetwork::ServerNetwork server_network(2525);
     server_network.Run();
     return 0;
}
