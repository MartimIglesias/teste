#pragma once
#include <iostream>
#include "Role.hpp"

namespace AAGame
{
    class Murderer : public Role {
    private:
        
    public:
        Murderer(const std::string& description = "You can kill someone each night.", const std::string& goal = "Kill everyone who would oppose you.");
        ~Murderer();
        std::string getDesctiption();
        std::string getGoal();
        void performAbility() override;
    };
}