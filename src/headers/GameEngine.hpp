#pragma once
#include <iostream>
#include <vector>
#include "User.hpp"
#include "servernetwork.hpp"

namespace AAGame
{
    class GameEngine {
    private:
        //debating on the pointers -> pointer means they exist outside the game class
        std::vector<AAGame::User*> Users;
        int gameState;

    public:
        GameEngine();
        ~GameEngine();

        //setters and getters------------------------
        AAGame::User* getUser();
        std::vector<AAGame::User*> getAllUsers();
        //-------------------------------------------

        // has to work for Player aswell
        bool AddUser();
        bool RemoveUser();
    };
}