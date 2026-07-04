#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics.hpp>

class Platform {
private:
    sf::Sprite sprite;
    sf::Vector2f position;

public:
    Platform(sf::Texture& texture, sf::Vector2f pos);

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
};

#endif