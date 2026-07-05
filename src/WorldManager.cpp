#include "WorldManager.hpp"
#include <random>
#include <limits>
#include <vector>

WorldManager::WorldManager(ResourceManager<sf::Texture>& texMgr)
    : textureManager(texMgr) {
    spawnInitialPlatforms();
}

static Platform::PlatformType getRandomPlatformType(std::mt19937 &gen) {
    std::uniform_int_distribution<int> typeDist(0, 4);
    int draw = typeDist(gen);
    if (draw == 0) {
        return Platform::PlatformType::Broken;
    }
    if (draw == 1) {
        return Platform::PlatformType::Moving;
    }
    return Platform::PlatformType::Normal;
}

static sf::Texture& getTextureForType(ResourceManager<sf::Texture>& manager, Platform::PlatformType type) {
    switch (type) {
        case Platform::PlatformType::Broken:
            return manager.get("platform_broken");
        case Platform::PlatformType::Moving:
            return manager.get("platform_moving");
        default:
            return manager.get("platform");
    }
}

void WorldManager::spawnInitialPlatforms() {
    auto &normalTex = textureManager.get("platform");
    platforms.push_back(Platform(normalTex, sf::Vector2f(200.f, 750.f), Platform::PlatformType::Normal));

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disXOffset(-180.f, 180.f);
    std::uniform_real_distribution<float> disY(70.f, 120.f);

    float currentY = 750.f;
    float currentX = 200.f;
    std::vector<float> occupiedYs;
    occupiedYs.push_back(currentY);

    for (int i = 0; i < 9; ++i) {
        float nextY;
        do {
            nextY = currentY - disY(gen);
        } while (std::any_of(occupiedYs.begin(), occupiedYs.end(), [&](float y) {
            return std::abs(y - nextY) < 60.f;
        }));

        currentY = nextY;
        occupiedYs.push_back(currentY);

        float nextX = currentX + disXOffset(gen);
        nextX = std::clamp(nextX, 0.f, 500.f - 100.f);
        currentX = nextX;

        Platform::PlatformType type = getRandomPlatformType(gen);
        sf::Texture &texture = getTextureForType(textureManager, type);
        platforms.push_back(Platform(texture, sf::Vector2f(nextX, currentY), type));
    }
}

float WorldManager::update(Player& player, float deltaTime) {
    if (player.getVelocity().y > 0.f) {
        sf::FloatRect playerBounds = player.getBounds();
        float playerBottom = playerBounds.top + playerBounds.height;

        for (auto& plat : platforms) {
            if (!plat.isActive()) {
                continue;
            }

            sf::FloatRect platBounds = plat.getBounds();
            if (playerBounds.intersects(platBounds)) {
                if (playerBottom < platBounds.top + platBounds.height) {
                    if (plat.getType() == Platform::PlatformType::Broken) {
                        plat.breakPlatform();
                    } else {
                        player.jump();
                    }
                    break;
                }
            }
        }
    }

    float scrollAmount = 0.f;
    if (player.getPosition().y < 400.f) {
        float diff = 400.f - player.getPosition().y;
        scrollAmount = diff;

        sf::Vector2f pPos = player.getPosition();
        pPos.y = 400.f;
        player.setPosition(pPos);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> disX(0.f, 400.f);
        std::uniform_real_distribution<float> disY(70.f, 150.f);

        float minY = std::numeric_limits<float>::max();
        for (auto& plat : platforms) {
            sf::Vector2f pos = plat.getPosition();
            pos.y += diff;
            plat.setPosition(pos);
            minY = std::min(minY, pos.y);
            plat.update(deltaTime, 500.f);
        }

        for (auto& plat : platforms) {
            if (plat.getPosition().y > 800.f) {
                float newY;
        do {
            newY = minY - disY(gen);
        } while (std::any_of(platforms.begin(), platforms.end(), [&](const Platform &other) {
            return std::abs(other.getPosition().y - newY) < 60.f;
        }));

        float newX = disX(gen);
        Platform::PlatformType type = getRandomPlatformType(gen);
        sf::Texture &texture = getTextureForType(textureManager, type);
        plat.reset(texture, type, sf::Vector2f(newX, newY));
        minY = newY;
            }
        }
    } else {
        for (auto& plat : platforms) {
            plat.update(deltaTime, 500.f);
        }
    }

    return scrollAmount;
}

void WorldManager::draw(sf::RenderWindow& window) {
    for (auto& plat : platforms) {
        plat.draw(window);
    }
}