#pragma once
#include <iostream>
#include "Role.hpp"

namespace AAGame
{
    class Villager : public Role {
    private:
        
    public:
        Villager(const std::string& description = "Well... You just kinda die...", const std::string& goal = "Lynch every criminal and evildoer.");
        ~Villager();
        std::string getDesctiption();
        std::string getGoal();
        void performAbility() override;
    };
}