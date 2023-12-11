#pragma once
#include <iostream>
#include <vector>
#include <atomic>
#include <thread>
#include <chrono>
#include <SFML/System/Clock.hpp>
#include <SFML/Network.hpp>
#include "EventHandler.hpp"
#include "Player.hpp"
#include "ThreadSafeVector.hpp"

const int _DAY_DURATION_ = 10;
const int _MINIMUM_PLAYER_COUNT_ = 2;
const int _MAX_EVENT_STRING_SIZE_ = 256;
const int _MAX_PLAYERS_ = 12;

namespace AAGame
{
    enum gamePhases {
            _DAY_,
            _NIGHT_,
            _NONE_
    };

    struct Vote
    {
        std::string name;
        int votes;
    };

    class GameEngine 
    {
    private:
        AANetwork::ThreadSafeVector<AAGame::Player> playerList;
        AANetwork::ThreadSafeVector<AAGame::Event> eventList;
        std::vector<AAGame::Vote> voteList;
        AAGame::gamePhases gamePhase;
        bool gameOver;
        std::string GE_ID;
        std::atomic<bool> gameRunning;

    public:
        GameEngine();

        //setters and getters------------------------
        AAGame::Player& getPlayer(std::string);
        AAGame::gamePhases getGamePhase();
        bool getGameRunning();
        void setGameRunning(bool);
        void setGamePhase(AAGame::gamePhases);
        void AddPlayer(std::string);
        void RemovePlayer(std::string);
        void RemovePlayerPos(int);
        void writeToEventList(AAGame::Event);
        AAGame::Event getEventListEntry(int);
        void pushEventListEntry(AAGame::Event);
        int getEventListSize();
        AAGame::Event popFirstEventListElement();
        //-------------------------------------------

        void Run();
        void allowChat();
        void Voting();
        void calculateResults(); 

        AAGame::Event processEvent(AAGame::Event);
        AAGame::Event ManageEvents(int, sf::Packet); // not done
    };
}