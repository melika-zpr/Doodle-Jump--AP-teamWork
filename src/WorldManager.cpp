#include "WorldManager.hpp"
#include <random>

WorldManager::WorldManager(ResourceManager<sf::Texture>& texMgr) 
    : textureManager(texMgr) {
    spawnInitialPlatforms();
}

void WorldManager::spawnInitialPlatforms() {
    sf::Texture& platTex = textureManager.get("platform");
    
    platforms.push_back(Platform(platTex, sf::Vector2f(200.f, 750.f)));
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(0.f, 400.f); 
    std::uniform_real_distribution<float> disY(70.f, 150.f);
    
    float currentY = 750.f;
    for (int i = 0; i < 9; ++i) {
        currentY -= disY(gen);
        platforms.push_back(Platform(platTex, sf::Vector2f(disX(gen), currentY)));
    }
}

void WorldManager::update(Player& player) {
    // ۱. بررسی برخورد بازیکن با سکوها
    if (player.getVelocity().y > 0.f) {
        sf::FloatRect playerBounds = player.getBounds();
        float playerBottom = playerBounds.top + playerBounds.height;
        
        for (auto& plat : platforms) {
            sf::FloatRect platBounds = plat.getBounds();
            if (playerBounds.intersects(platBounds)) {
                if (playerBottom < platBounds.top + platBounds.height) {
                    player.jump();
                    break;
                }
            }
        }
    }

    // ۲. مدیریت حرکت دوربین (اسکرول صفحه) و بازیافت سکوها
    if (player.getPosition().y < 400.f) {
        float diff = 400.f - player.getPosition().y;
        
        sf::Vector2f pPos = player.getPosition();
        pPos.y = 400.f;
        player.setPosition(pPos);
        
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> disX(0.f, 400.f);

        for (auto& plat : platforms) {
            sf::Vector2f pos = plat.getPosition();
            pos.y += diff; 
            
            // اگر سکو از پایین خارج شد، به بالا منتقل می‌شود
            if (pos.y > 800.f) {
                pos.y = 0.f;
                pos.x = disX(gen);
            }
            plat.setPosition(pos);
        }
    }
}

void WorldManager::draw(sf::RenderWindow& window) {
    for (auto& plat : platforms) {
        plat.draw(window);
    }
}