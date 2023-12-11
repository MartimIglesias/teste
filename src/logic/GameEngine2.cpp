#include "..\headers\GameEngine2.hpp"

AAGame::GameEngine::GameEngine()
    :   playerList(),
        eventList(),
        voteList(),
        gamePhase(AAGame::gamePhases::_NONE_),
        gameOver(false),
        gameRunning(false),
        GE_ID("0")
{

}

AAGame::Player& AAGame::GameEngine::getPlayer(std::string name)
{
    for (size_t iterator = 0; iterator < this->playerList.size(); iterator++)
    {
        if (name.compare(playerList[iterator].getName()) == 0)
        {
            return playerList[iterator];
        }
    }
    static AAGame::Player p("none");
    return p;
}

/*std::vector<AAGame::Player>& AAGame::GameEngine::getAllPlayers()
{
    return this->playerList;
}*/

AAGame::gamePhases AAGame::GameEngine::getGamePhase()
{
    return this->gamePhase;
}

bool AAGame::GameEngine::getGameRunning()
{
    return this->gameRunning;
}

void AAGame::GameEngine::setGameRunning(bool b)
{
    this->gameRunning = b;
}

void AAGame::GameEngine::setGamePhase(AAGame::gamePhases gp)
{
    this->gamePhase = gp;
}

void AAGame::GameEngine::AddPlayer(std::string name)
{
    AAGame::Player p(name);
    this->playerList.push_back(p);
}

void AAGame::GameEngine::RemovePlayer(std::string name)
{
    for (size_t iterator = 0; iterator < this->playerList.size(); iterator++)
    {
        if (name.compare(playerList[iterator].getName()) == 0) playerList.erase(playerList.begin() + iterator);
    }
}

void AAGame::GameEngine::RemovePlayerPos(int pos)
{
    playerList.erase(playerList.begin() + pos);
}

void AAGame::GameEngine::writeToEventList(AAGame::Event ev)
{
    this->eventList.push_back(ev);
}

AAGame::Event AAGame::GameEngine::getEventListEntry(int pos)
{
    return this->eventList[pos];
}

void AAGame::GameEngine::pushEventListEntry(AAGame::Event ev)
{
    this->eventList.push_back(ev);
}

int AAGame::GameEngine::getEventListSize()
{
    return this->eventList.size();
}

AAGame::Event AAGame::GameEngine::popFirstEventListElement()
{
    return this->eventList.pop_front();
}

/*void AAGame::GameEngine::HandlePlayers()
{   
    while(gameRunning == false) 
    {
        int player_count = this->playerList.size();
        if (player_count < this->server.getClientCount())
        {
            for (int dif = this->server.getClientCount() - player_count; dif > 0; dif--)
            {
                // potentially dangerous(empty player)!!!!!!!!!!!!!!!!
                std::string name = *(this->server.getAllNames().end() - dif - 1);
                AAGame::Player p(name);
                playerList.push_back(p);
                std::cout << "Player added, name == " << name << "\n";
            }
        }
        if (player_count > this->server.getClientCount())
        {
            std::vector<std::string> names = this->server.getAllNamesGone();

            for (int nameGonePos = 0; nameGonePos < names.size(); nameGonePos++)
            {
                for (int playerPos = 0; playerPos < playerList.size(); playerPos++)
                {
                    if (names[nameGonePos].compare(playerList[playerPos].getName()) == 0)
                    {
                        playerList.erase(playerList.begin() + playerPos);
                        break;
                    }
                }
            }
            this->server.cleanAllNamesGone();
        }

    if (this->playerList.size() >= _MINIMUM_PLAYER_COUNT_)
    {
        this->gameRunning = true;
        this->server.setCheckCons(false);
    }
    std::cout << "Still trying..." << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
*/


void AAGame::GameEngine::allowChat()
{
    AAGame::Event chat_green_light_ev(AAGame::Event::EventType::CHAT_GREEN_LIGHT, this->GE_ID, "-1","Players can chat!");
    pushEventListEntry(chat_green_light_ev);

    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    while (elapsed.asSeconds() <= _DAY_DURATION_)
    {
        elapsed = clock.getElapsedTime();
    }

    AAGame::Event chat_red_light_ev(AAGame::Event::EventType::CHAT_RED_LIGHT, this->GE_ID, "-1","Players can't chat!");
    pushEventListEntry(chat_red_light_ev);
}

void AAGame::GameEngine::Voting()
{
    AAGame::Event voting_green_ev(AAGame::Event::VOTING_GREEN_LIGHT,  this->GE_ID, "-1", "Players can now Vote!");
    pushEventListEntry(voting_green_ev);

    sf::Clock clock;
    sf::Time elapsed = clock.restart();
    while (elapsed.asSeconds() <= _DAY_DURATION_)
    {
        elapsed = clock.getElapsedTime();
    }
    
    AAGame::Event voting_red_ev(AAGame::Event::EventType::VOTING_RED_LIGHT,  this->GE_ID, "-1", "Players can't vote!");
    pushEventListEntry(voting_red_ev);
}

void AAGame::GameEngine::calculateResults()
{

}

/*AAGame::Event AAGame::GameEngine::fetchEventPos(int pos)
{
    std::string s = this->getEventListEntry(pos);

    AAGame::Event ev(s);

    return ev;
}*/

AAGame::Event AAGame::GameEngine::processEvent(AAGame::Event ev)
{
    AAGame::Event::EventType eventType = ev.getType();
    std::string details = ev.getDetails();
    std::vector<std::string> details_vec;

    AAGame::Event response_ev;
    switch (eventType) 
    {
        case AAGame::Event::EventType::PLAYER_ABILITY:
            /*AAGame::Player& user = this->getPlayer(ev.getSenderName());
            AAGame::Player& receiver = this->getPlayer(ev.getReceiverName());
            user.performAbility(receiver);
            //response_ev...*/
            break;
        case AAGame::Event::EventType::CHAT_MESSAGE:
            break;
        default:
            break;
    }

    return response_ev;
}

AAGame::Event AAGame::GameEngine::ManageEvents(int pos, sf::Packet pckt)
{
    std::string received_message;
    pckt >> received_message;

    AAGame::Event ev(received_message);

    AAGame::Event response_ev = this->processEvent(ev);

    return response_ev;
}

// ONLY THE STRUCTURE OF THE GAME , the actions are performed only on events hence another thread deals with that not this one
void AAGame::GameEngine::Run()
{
    while(this->gameOver == false)
    {

        std::cout << "Waiting for players to join (minimum 5)!" << "\n";

        while(this->getGameRunning() == true)
        {
            
            if(this->gamePhase == AAGame::gamePhases::_DAY_)
            {
                // communication
                this->allowChat();
                // voting
                this->Voting();
                AAGame::Event test_ev(AAGame::Event::PLAYER_ABILITY, "1", "2", "PLayer 0 killed player 1(You)!");
                pushEventListEntry(test_ev);
                // change gs
                this->setGamePhase(AAGame::gamePhases::_NIGHT_);
            }
            else
            {
                // every player can use abilities
                /*for (size_t iterator = 0; iterator < this->playerList.size(); iterator++)
                {
                    this->playerList[iterator].setPlayerPerform(true);
                }
                // results
                this->calculateResults();*/
                // change gs
                std::cout << "NIGHT" << "\n";
                std::this_thread::sleep_for((std::chrono::milliseconds)500);
                this->setGamePhase(AAGame::gamePhases::_DAY_);
            }

            // UPDATE

        }
        std::this_thread::sleep_for((std::chrono::milliseconds)500);
    }
}