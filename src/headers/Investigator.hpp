#pragma once
#include <iostream>

namespace AAGame
{
    class Investigator : public Role {
    private:
        
    public:
        Investigator(const std::string& description = "Investigate one person each night for a clue to their role.", const std::string& goal = "Lynch every criminal and evildoer.");
        ~Investigator();
        std::string getDesctiption();
        std::string getGoal();
        void performAbility() override;
    };
}