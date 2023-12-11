#ifndef ROLES_HPP
#define ROLES_HPP

#include <string>
#include <vector>
#include "Player.hpp"  // Supondo que temos uma classe Player separada

class Role 
{
    protected:
        std::string roleName;

    public:
        Role(std::string name) : roleName(name) {}

        virtual void performNightAction(std::vector<Player>& players) = 0;
        virtual ~Role() = default;
};

class SK : public Role 
{
    public:
        SK() : Role("Salazar") {}
        void performNightAction(std::vector<Player>& players) override;
};

class Mafia : public Role 
{
    public:
        Mafia() : Role("PIDE") {}
        void performNightAction(std::vector<Player>& players) override;
};

class Doutor : public Role 
{
    public:
        Doutor() : Role("Miguel Torga") {}
        void performNightAction(std::vector<Player>& players) override;
};

class Investigador : public Role 
{
    public:
        Investigador() : Role("Inspetor Max") {}
        void performNightAction(std::vector<Player>& players) override;
};

class Aldeao : public Role 
{
    public:
        Aldeao() : Role("Zé Povinho") {}
        void performNightAction(std::vector<Player>& players) override;
};

#endif  // ROLES_HPP
