#pragma once
#include <iostream>
#include "clientnetwork.hpp"
#include "Entity.hpp"
#include "EventHandler.hpp"

namespace AAGame 
{   
    class User : public EventHandler{
    private:
        std::string name;
        AANetwork::ClientNetwork client;
        AAGame::Entity entity;
        
    public:
        User(std::string name);
        ~User();

        void UpdateEntity(AAGame::Event);
        // void reportEntityChanges();

    };
    
}