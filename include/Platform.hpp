#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics.hpp>

class Platform {
public:
    enum class PlatformType {
        Normal,
        Broken,
        Moving
    };

private:
    sf::Sprite sprite;
    sf::Vector2f position;
    PlatformType type;
    bool active;
    float moveSpeed;
    int moveDirection;

public:
    Platform(sf::Texture& texture, sf::Vector2f pos, PlatformType type = PlatformType::Normal);

    void update(float deltaTime, float windowWidth);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    void reset(sf::Texture& texture, PlatformType type, sf::Vector2f pos);
    bool isActive() const;
    void breakPlatform();
    PlatformType getType() const;
};

#endif