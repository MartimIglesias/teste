#pragma once
#include <iostream>
#include <SFML\System\Vector2.hpp>
#include <SFML\Graphics\Texture.hpp>

namespace AAGame
{
    class Entity {
    private:
        sf::Vector2<float> pos;
        sf::Vector2<float> velocity;
        float rotation;
        int health;
        int scale;  
        std::shared_ptr<sf::Texture> sprite;
    public:
        Entity();
        Entity(sf::Vector2<float> pos, sf::Vector2<float> velocity, 
        float rotation, int health, int scale, std::shared_ptr<sf::Texture> ptr);
        ~Entity();

        //setters and getters------------------------
        void setPosition(sf::Vector2<float>& position);
        sf::Vector2<float> getPosition() const;
        void setVelocity(sf::Vector2<float>& vel);
        sf::Vector2<float> getVelocity() const;
        void setRotation(float& rot);
        float getRotation() const;
        void setHealth(int& h);
        int getHealth() const;
        void setScale(int& s);
        int getScale() const;
        std::shared_ptr<sf::Texture> getSprite() const;
        // -------------------------------------------

        void Update();
        void Render();
    };
}
