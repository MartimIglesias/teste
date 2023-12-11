#include <iostream>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Image.hpp>
#include "..\headers\Entity.hpp"

// Constructor
AAGame::Entity::Entity()
    : pos(0.0f, 0.0f),
      velocity(0.0f, 0.0f),   
      rotation(0.0f),         
      health(100),            
      scale(1),               
      sprite(nullptr)
{}

AAGame::Entity::Entity(sf::Vector2<float> pos, sf::Vector2<float> velocity, 
float rotation, int health, int scale, std::shared_ptr<sf::Texture> ptr)
    : pos(pos.x, pos.y),
      velocity(velocity.x, velocity.y),
      rotation(rotation),
      health(health),
      scale(scale),
      sprite(ptr)
{}

// Default destructor

// SETTERS --------------------------------------------
void AAGame::Entity::setPosition(sf::Vector2<float>& position)
{
            this->pos = position;
}

void AAGame::Entity::setVelocity(sf::Vector2<float>& velocity)
{
            this->velocity = velocity;
}

void AAGame::Entity::setRotation(float& rot)
{
            this->rotation = rot;
}

void AAGame::Entity::setHealth(int& h)
{
            this->health = h;
}

void AAGame::Entity::setHealth(int& s)
{
            this->scale = s;
}

// ----------------------------------------------------

// GETTERS --------------------------------------------

sf::Vector2<float> AAGame::Entity::getPosition() const
{
            return pos;
}

sf::Vector2<float> AAGame::Entity::getVelocity() const
{
            return velocity;
}

float AAGame::Entity::getRotation() const
{
            return rotation;
}

int AAGame::Entity::getHealth() const
{
            return health;
}

int AAGame::Entity::getScale() const
{
            return scale;
}

std::shared_ptr<sf::Texture> AAGame::Entity::getSprite() const
{
            return sprite;
}

// ----------------------------------------------------