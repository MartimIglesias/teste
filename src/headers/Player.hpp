#pragma once
#include <iostream>
#include "Role.hpp"
#include "Event.hpp"


namespace AAGame 
{
    
    class Player{
    private:
        std::string name;
        std::string faction;
        
        int voteCount;
        bool canPerform;
    public:
        Player(std::string name);

        std::string getName();
        void setName(std::string&);
        void setFaction(std::string&);
        std::string getFaction();
        void setPlayerPerform(bool);
        void incrementVoteCount();
        void resetVoteCount();
        int getVoteCount();

        void performAbility(AAGame::Player&);
    };

}