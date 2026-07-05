#ifndef WORLDMANAGER_HPP
#define WORLDMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Platform.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"

class WorldManager {
private:
    std::vector<Platform> platforms;
    
    // ارجاع به مدیر منابع برای دسترسی به عکس سکوها
    ResourceManager<sf::Texture>& textureManager;

public:
    WorldManager(ResourceManager<sf::Texture>& texMgr);

    void spawnInitialPlatforms();
    
    // بازیکن به عنوان ورودی داده می‌شود تا برخوردها و دوربین محاسبه شود
    float update(Player& player, float deltaTime);
    
    void draw(sf::RenderWindow& window);
};

#endif