#include "Game.hpp"
#include <iostream>

Game::Game() : window(sf::VideoMode(500, 800), "Doodle Jump - Phase 1", sf::Style::Titlebar | sf::Style::Close)
{
    window.setFramerateLimit(60);

    try
    {
        // توجه: نام فایل در مسیر زیر باید با نام عکس شما در پوشه assets یکی باشد
        sf::Texture &texLeft = textureManager.load("player_left", "assets/left_doodle.png");
        sf::Texture &texRight = textureManager.load("player_right", "assets/right_doodle.png");

        // عکس سکو باید قبل از ساختن WorldManager لود شود
        textureManager.load("platform", "assets/normal_platform.png");

        player = std::make_unique<Player>(texLeft, texRight);

        // ساختن مدیر دنیای بازی و پاس دادن منابع به آن
        worldManager = std::make_unique<WorldManager>(textureManager);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Initialization Error: " << e.what() << std::endl;
    }
}

void Game::run()
{
    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }

    if (player)
    {
        player->handleInput();
    }
}

void Game::update(float deltaTime)
{
    if (player && worldManager)
    {
        // آپدیت فیزیک بازیکن
        player->update(deltaTime, 500.f);

        // آپدیت برخوردها و دوربین با پاس دادن بازیکن به دنیای بازی
        worldManager->update(*player);
    }
}

void Game::render()
{
    // تغییر رنگ پس‌زمینه به خاکستری روشن برای دیده شدن بهتر کاراکتر
    window.clear(sf::Color(240, 240, 240));

    // رسم سکوها
    if (worldManager)
    {
        worldManager->draw(window);
    }

    // رسم بازیکن (همیشه بعد از سکوها رسم می‌شود تا روی آن‌ها قرار بگیرد)
    if (player)
    {
        player->draw(window);
    }

    window.display();
}