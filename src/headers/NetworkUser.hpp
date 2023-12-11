#pragma once
#include <iostream>
#include "clientnetwork.hpp"
#include "Event.hpp"

namespace AANetwork
{
    // a class that creates/shares and receives events (wrapper over client)
    class NetworkUser {
    private:
        // inheritance -> User (has a) Client -> composition -> the client should be destroyed when the User is destroyed
        std::string name;
        AANetwork::ClientNetwork client;
        AAGame::Event last_event;
    public:
        NetworkUser();
        ~NetworkUser();

        std::string getName();
        AAGame::Event getLastEvent();

        AAGame::Event createEvent();
        void receiveEvent(AAGame::Event);
    };
}