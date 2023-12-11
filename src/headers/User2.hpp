#pragma once
#include <iostream>
#include <SFML/Network.hpp>
#include "Event.hpp"
//#include "Entity.hpp"
#include "ThreadSafeVector.hpp"

namespace AAGame 
{   
    class User {
    private:
        std::string name;
        AANetwork::ThreadSafeVector<AAGame::Event> eventList;

        bool canChat;
    public:
        User(std::string name);
        User();

        void pushEventListEntry(AAGame::Event);
        int getEventListSize();
        AAGame::Event popFirstEventListElement();

        AAGame::Event processEvent(AAGame::Event);
        AAGame::Event ManageEvents(sf::Packet);
    };
}