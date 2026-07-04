#include "Platform.hpp"

Platform::Platform(sf::Texture& texture, sf::Vector2f pos) {
    sprite.setTexture(texture);
    position = pos;
    sprite.setPosition(position);
}

void Platform::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Platform::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Platform::getPosition() const {
    return position;
}

void Platform::setPosition(sf::Vector2f pos) {
    position = pos;
    sprite.setPosition(position);
}