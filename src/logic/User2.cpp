#include "..\headers\User2.hpp"

AAGame::User::User(std::string name)
    :   name(name),
        eventList(),
        canChat(false)
{

}

AAGame::User::User()
    :   name(),
        eventList(),
        canChat(true)
{

}

void AAGame::User::pushEventListEntry(AAGame::Event ev)
{
    this->eventList.push_back(ev);
}

int AAGame::User::getEventListSize()
{
    return this->eventList.size();
}

AAGame::Event AAGame::User::popFirstEventListElement()
{
    return this->eventList.pop_front();
}

AAGame::Event AAGame::User::processEvent(AAGame::Event ev)
{
    AAGame::Event::EventType eventType = ev.getType();
    std::string details = ev.getDetails();
    std::vector<std::string> details_vec;

    AAGame::Event response_ev;
    switch (eventType)
    {
        case AAGame::Event::EventType::CHAT_GREEN_LIGHT:
            this->canChat = true;
            break;
        case AAGame::Event::EventType::CHAT_RED_LIGHT:
            this->canChat = false;
            break;
        default:
            break;
    }

    return response_ev;
}

AAGame::Event AAGame::User::ManageEvents(sf::Packet pckt)
{
    std::string received_message;
    pckt >> received_message;

    AAGame::Event ev(received_message);
    
    AAGame::Event response_ev = this->processEvent(ev);

    return response_ev;
}