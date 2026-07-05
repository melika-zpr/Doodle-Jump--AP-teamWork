#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "ResourceManager.hpp"
#include "Player.hpp"
#include "WorldManager.hpp"

class Game {
private:
    enum class GameState {
        Menu,
        Playing,
        GameOver
    };

    sf::RenderWindow window;
    sf::Clock clock;

    ResourceManager<sf::Texture> textureManager;

    std::unique_ptr<Player> player;
    std::unique_ptr<WorldManager> worldManager;

    sf::Sprite backgroundSprite;
    sf::Font font;
    sf::Text titleText;
    sf::Text subtitleText;
    sf::Text actionText;
    sf::Text restartText;
    sf::Text menuText;
    sf::Text scoreText;
    sf::Text highScoreText;
    sf::Text menuHighScoreText;
    sf::Text instructionText;
    sf::Text gameOverText;

    sf::RectangleShape startButton;
    sf::RectangleShape restartButton;
    sf::RectangleShape menuButton;

    int score;
    int highScore;

    GameState gameState;

    void processEvents();
    void update(float deltaTime);
    void render();

    void setupUi();
    void updateOverlayTexts();
    void startGame();
    void resetGame();
    void handleButtonClick(const sf::Vector2i &mousePosition);
    void drawOverlay();

public:
    Game();
    void run();
};

#endif