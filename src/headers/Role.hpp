#pragma once
#include <iostream>

namespace AAGame
{
    class Role {
    private:
        std::string faction;
        std::string description;
        std::string goal;
        
    public:
        Role(std::string faction);
        ~Role();
        std::string getFaction();
        virtual void performAbility() ;
    };
}