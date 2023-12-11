#pragma once
#include <iostream>
#include <vector>
#include "clientnetwork.hpp"

#define loggl(x) std::cout << x << std::endl
#define logg(x) std::cout << x

namespace AANetwork 
{
    class Chat : public ClientNetwork{
        std::vector<std::string> users;
        std::vector<std::string> msgs;

    public:
        Chat();
        void Run();

    };

} // namespace AANetwork