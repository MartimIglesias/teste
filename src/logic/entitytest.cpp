#include <gtest/gtest.h>
#include "..\headers\Entity.hpp"

class EntityTest : public ::testing::Test {
protected:
    AAGame::Entity defaultEntity;
    sf::Vector2<float> initialPosition{10.0f, 10.0f};
    sf::Vector2<float> initialVelocity{2.0f, 2.0f};
    float initialRotation{45.0f};
    int initialHealth{100};
    int initialScale{1};
    std::shared_ptr<sf::Texture> initialTexture{std::make_shared<sf::Texture>()};

    AAGame::Entity customEntity{initialPosition, initialVelocity, initialRotation, initialHealth, initialScale, initialTexture};
    
    void SetUp() override {
        // Setup code (if needed)
    }

    void TearDown() override {
        // Cleanup code (if needed)
    }
};

TEST_F(EntityTest, Constructor_DefaultValues) {
    EXPECT_EQ(defaultEntity.getPosition(), sf::Vector2<float>(0.0f, 0.0f));
    EXPECT_EQ(defaultEntity.getVelocity(), sf::Vector2<float>(0.0f, 0.0f));
    EXPECT_EQ(defaultEntity.getRotation(), 0.0f);
    EXPECT_EQ(defaultEntity.getHealth(), 100); // Assuming the default health is 100
    EXPECT_EQ(defaultEntity.getScale(), 1); // Assuming the default scale is 1
    EXPECT_EQ(defaultEntity.getSprite(), nullptr);
}

TEST_F(EntityTest, Constructor_CustomValues) {
    EXPECT_EQ(customEntity.getPosition(), initialPosition);
    EXPECT_EQ(customEntity.getVelocity(), initialVelocity);
    EXPECT_EQ(customEntity.getRotation(), initialRotation);
    EXPECT_EQ(customEntity.getHealth(), initialHealth);
    EXPECT_EQ(customEntity.getScale(), initialScale);
    EXPECT_EQ(customEntity.getSprite(), initialTexture);
}

TEST_F(EntityTest, SetGetPosition) {
    sf::Vector2<float> newPosition{20.0f, 20.0f};
    defaultEntity.setPosition(newPosition);
    EXPECT_EQ(defaultEntity.getPosition(), newPosition);
}

TEST_F(EntityTest, SetGetVelocity) {
    sf::Vector2<float> newVelocity{5.0f, 5.0f};
    defaultEntity.setVelocity(newVelocity);
    EXPECT_EQ(defaultEntity.getVelocity(), newVelocity);
}

TEST_F(EntityTest, SetGetRotation) {
    float newRotation = 90.0f;
    defaultEntity.setRotation(newRotation);
    EXPECT_EQ(defaultEntity.getRotation(), newRotation);
}

TEST_F(EntityTest, SetGetHealth) {
    int newHealth = 75;
    defaultEntity.setHealth(newHealth);
    EXPECT_EQ(defaultEntity.getHealth(), newHealth);
}

TEST_F(EntityTest, SetGetScale) {
    int newScale = 2;
    defaultEntity.setScale(newScale);
    EXPECT_EQ(defaultEntity.getScale(), newScale);
}

// Adicione mais testes conforme necessário para cobrir todos os métodos e cenários possíveis