#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "ResourceManager.hpp"
#include "Player.hpp"
#include "WorldManager.hpp"

class Game {
private:
    sf::RenderWindow window;
    sf::Clock clock;

    ResourceManager<sf::Texture> textureManager;
    // استفاده از unique_ptr برای مدیریت هوشمند حافظه و جلوگیری از نشت حافظه
    std::unique_ptr<Player> player;

    // اضافه شدن کلاس مدیریت دنیای بازی
    std::unique_ptr<WorldManager> worldManager;

    // متغیر جدید برای اسپرایت پس‌زمینه
    sf::Sprite backgroundSprite;

    void processEvents();
    void update(float deltaTime);
    void render();

public:
    Game();
    void run();
};

#endif