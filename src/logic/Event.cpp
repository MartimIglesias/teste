#include "..\headers\Event.hpp"

AAGame::Event::EventType stringToEventType(const std::string& s);

//Constructor

AAGame::Event::Event()
    :   type(AAGame::Event::EventType::DEFAULT),
        details(""),
        sender_id(""),
        receiver_id("")
{
    
}

/*
AAGame::Event::Event(EventType type, const std::string details)
        :   type(type),
            details(details),
            sender_id(),
            receiver_id()
{
    
}
*/
AAGame::Event::Event(std::string s)
{
    // creates a string stream
    std::istringstream s_stream(s);
    std::string str_hold;
    char delimiter = ';';

    // goes to input stream s_stream and dumps everything that is between ";" into str_hold 
    std::getline(s_stream, str_hold, delimiter);

    std::string discard;
    std::string str_type;
    std::string str_sender_id;
    std::string str_receiver_id;
    
    // dump each part into each member, discarding start and end macro
    s_stream >> discard;
    s_stream >> str_type;
    type = StringToEventType(str_type);
    s_stream >> sender_id;
    s_stream >> receiver_id;
    //sender_id = stoi(str_sender_id);d
    //receiver_id = stoi(str_receiver_id);
    s_stream >> details;
    s_stream >> discard;
}

AAGame::Event::Event(EventType t, std::string s_id, std::string r_id, std::string s)
    :   type(t), 
        sender_id(s_id),
        receiver_id(r_id),
        details(s) 
{

}

// Default destructor

// GETTERS --------------------------------------------

AAGame::Event::EventType AAGame::Event::getType() const 
{
    return type;
}

std::string AAGame::Event::getDetails() const 
{
    return details;
}

std::string AAGame::Event::getReceiverName()
{
    return receiver_id;
}

// ----------------------------------------------------

// Helper Functions -----------------------------------

bool AAGame::Event::isEmpty()
{
    if (getType() == AAGame::Event::EventType::DEFAULT) return true;
    return false;
}

std::string eventTypeToString(AAGame::Event::EventType& eventType)
{
    std::string s;
    switch (eventType)
    {
        case AAGame::Event::EventType::DEFAULT:
            s = "DEFAULT";
            break;
        case AAGame::Event::EventType::PLAYER_ABILITY:
            s = "PLAYER_ABILITY";
            break;
        case AAGame::Event::EventType::CHAT_MESSAGE:
            s = "CHAT_MESSAGE";
            break;
        case AAGame::Event::EventType::VOTING_GREEN_LIGHT:
            s = "VOTING_GREEN_LIGHT";
            break;
        case AAGame::Event::EventType::VOTING_RED_LIGHT:
            s = "VOTING_RED_LIGHT";
            break;
        case AAGame::Event::EventType::CHAT_GREEN_LIGHT:
            s = "CHAT_GREEN_LIGHT";
            break;
        case AAGame::Event::EventType::CHAT_RED_LIGHT:
            s = "CHAT_RED_LIGHT";
            break;
    }
    return s;
}

AAGame::Event::EventType AAGame::Event::StringToEventType(std::string s)
{   
    if (s == "DEFAULT") {
        return AAGame::Event::EventType::DEFAULT;
    } else if (s == "PLAYER_ABILITY") {
        return AAGame::Event::EventType::PLAYER_ABILITY;
    } else if (s == "CHAT_MESSAGE") {
        return AAGame::Event::EventType::CHAT_MESSAGE;
    } else if (s == "VOTING_GREEN_LIGHT") {
        return AAGame::Event::EventType::VOTING_GREEN_LIGHT;
    } else if (s == "VOTING_RED_LIGHT") {
        return AAGame::Event::EventType::VOTING_RED_LIGHT;
    } else if (s == "CHAT_GREEN_LIGHT") {
        return AAGame::Event::EventType::CHAT_GREEN_LIGHT;
    } else if (s == "CHAT_RED_LIGHT") {
        return AAGame::Event::EventType::CHAT_RED_LIGHT;
    }
    
    return AAGame::Event::EventType::INVALID;
}

// ----------------------------------------------------

// Member Functions -----------------------------------

std::string AAGame::Event::EventToString()
{
    std::string event(_START_MACRO);
    
    event += ";" + eventTypeToString(type) + ";" + sender_id + ";" + receiver_id + ";" + details + ";" + _END_MACRO;

    return event;
}

// ----------------------------------------------------
