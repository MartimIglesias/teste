#include "..\headers\Player.hpp"

AAGame::Player::Player(std::string name)
    : name(name),
    faction(),
    canPerform(0)
{

}

std::string AAGame::Player::getName()
{
    return this->name;
}

void AAGame::Player::setName(std::string& newName)
{
    name = newName;
}

void AAGame::Player::setFaction(std::string& newFaction)
{
    faction = newFaction;
}

std::string AAGame::Player::getFaction()
{
    return faction;
}

void AAGame::Player::setPlayerPerform(bool canPerform)
{
    this->canPerform = canPerform;
}

void AAGame::Player::incrementVoteCount()
{
    voteCount++;
}

void AAGame::Player::resetVoteCount()
{
    voteCount = 0;
}

int AAGame::Player::getVoteCount()
{
    return voteCount;
}

void AAGame::Player::performAbility(Player& target)
{
    std::cout << "Ability Performed!" << "\n";
}
