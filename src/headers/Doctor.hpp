#pragma once
#include <iostream>
#include "Role.hpp"

namespace AAGame
{
    class Doctor : public Role {
    private:
        
    public:
        Doctor(const std::string& description = "Heal one person each night, preventing them from dying.", const std::string& goal = "Lynch every criminal and evildoer.");
        ~Doctor();
        std::string getDesctiption();
        std::string getGoal();
        void performAbility() override;
    }
}