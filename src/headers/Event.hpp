#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define _START_MACRO "__START__"
#define _END_MACRO "__END__"
const int _GAME_ENGINE_ID = 100;

namespace AAGame
{
    class Event {

    // EVENT STRING LAYOUT : START_MACRO;type;sender_id;receiver_id;details;END_MACRO
    // details = sender_name;receiver_name;
    // DISCLAIMER: receiver_id is an identifier for who «««should»»» receive the event, if player A
    // kills player B than every User should/needs (to) know that, not just player B.

    public:
        enum EventType {
            DEFAULT,
            PLAYER_ABILITY,
            CHAT_MESSAGE,
            VOTING_GREEN_LIGHT,
            VOTING_RED_LIGHT,
            CHAT_GREEN_LIGHT,
            CHAT_RED_LIGHT,
            INVALID,
        };

    /*Event()
    Event(EventType t, std::string s);
    Event(std::string s);*/
    Event();
    Event(std::string);
    Event(EventType t, std::string s_id, std::string r_id, std::string details);

    //setters and getters------------------------
    EventType getType() const;
    std::string getDetails() const;
    std::string getSenderName();
    std::string getReceiverName();
    //-------------------------------------------

    bool isEmpty();
    AAGame::Event::EventType StringToEventType(std::string); 
    std::string EventToString();

    private:
        EventType type;
        std::string details;
        std::string sender_id;
        std::string receiver_id;
    };
}