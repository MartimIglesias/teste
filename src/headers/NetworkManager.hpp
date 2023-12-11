#pragma once
#include <iostream>
#include <vector>
#include "NetworkUser.hpp"
#include "servernetwork.hpp"

namespace AANetwork
{
    class NetworkManager {
    private:
        //debating on the pointers -> pointer means they exist outside the networkmanager class
        std::vector<AANetwork::NetworkUser*> Users;
        AANetwork::ServerNetwork server;

    public:
        NetworkManager();
        NetworkManager(unsigned short port);
        ~NetworkManager();

        AANetwork::NetworkUser* getUser(std::string name);

        void Run();
        void UpdateNetwork();
        bool AddUser();
        bool RemoveUser();
        void receiveEventFromUser(std::string event_sender);
    };
}