#pragma once
#include <iostream>
#include <vector>
#include "GameEngine.hpp"
#include "NetworkManager.hpp"

#define PORT_NUMBER 2525

namespace AAGame
{
    class Game {
        

    public:
        //must be called before anything else probably should be the constructor
        void Start();

    };
}