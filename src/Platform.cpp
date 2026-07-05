#include "Platform.hpp"

Platform::Platform(sf::Texture& texture, sf::Vector2f pos, PlatformType platformType)
    : position(pos), type(platformType), active(true), falling(false), moveSpeed(0.f), fallSpeed(160.f), moveDirection(1)
{
    sprite.setTexture(texture);
    sprite.setPosition(position);
    if (type == PlatformType::Moving) {
        moveSpeed = 80.f;
    }
}

void Platform::update(float deltaTime, float windowWidth) {
    if (type == PlatformType::Moving && active) {
        position.x += moveSpeed * static_cast<float>(moveDirection) * deltaTime;
        if (position.x < 0.f) {
            position.x = 0.f;
            moveDirection = 1;
        } else if (position.x + sprite.getGlobalBounds().width > windowWidth) {
            position.x = windowWidth - sprite.getGlobalBounds().width;
            moveDirection = -1;
        }
    }

    if (falling) {
        position.y += fallSpeed * deltaTime;
        if (position.y > 900.f) {
            active = false;
            falling = false;
        }
    }

    sprite.setPosition(position);
}

void Platform::draw(sf::RenderWindow& window) {
    if (active || falling) {
        window.draw(sprite);
    }
}

sf::FloatRect Platform::getBounds() const {
    if (!active) {
        return sf::FloatRect();
    }
    return sprite.getGlobalBounds();
}

sf::Vector2f Platform::getPosition() const {
    return position;
}

void Platform::setPosition(sf::Vector2f pos) {
    position = pos;
    sprite.setPosition(position);
}

void Platform::reset(sf::Texture& texture, PlatformType newType, sf::Vector2f pos) {
    type = newType;
    active = true;
    position = pos;
    sprite.setTexture(texture);
    sprite.setPosition(position);
    moveDirection = 1;
    moveSpeed = (type == PlatformType::Moving) ? 80.f : 0.f;
}

bool Platform::isActive() const {
    return active;
}

void Platform::breakPlatform() {
    if (type == PlatformType::Broken) {
        active = false;
    }
}

Platform::PlatformType Platform::getType() const {
    return type;
}