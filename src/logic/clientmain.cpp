#include "..\headers\clientnetwork.hpp"

int main()
{
    AANetwork::ClientNetwork c("localHost", 2525);
    c.Run();
}