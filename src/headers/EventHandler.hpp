#pragma once
#include <iostream>
#include "Event.hpp"

namespace AAGame 
{
    class EventHandler
    {
    public:
        EventHandler();

        virtual void sendEvent();
        virtual AAGame::Event fetchEvent();
        virtual AAGame::Event fetchEventPos(int);
        virtual AAGame::Event processEvent(AAGame::Event);
        // void BroadcastEvent(AAGame::Event);
        virtual void ManageEvents();
    };
}