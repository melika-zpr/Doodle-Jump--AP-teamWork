#include "Player.hpp"

Player::Player(sf::Texture &textureLeft, sf::Texture &textureRight)
{
    // ذخیره آدرس تکستچرها
    texLeft = &textureLeft;
    texRight = &textureRight;

    // تنظیم تصویر اولیه (مثلاً رو به راست)
    sprite.setTexture(*texRight);

    // مرکز تصویر را برای دقیق‌تر شدن پیچش صفحه وسط در نظر می‌گیریم
    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);

    // موقعیت اولیه
    position = sf::Vector2f(250.f, 400.f);
    velocity = sf::Vector2f(0.f, 0.f);

    score = 0;
    movementSpeed = 400.f; // سرعت حرکت افقی
    gravity = 900.f;       // شتاب گرانش رو به پایین
    jumpForce = -650.f;    // نیروی پرش اولیه رو به بالا (منفی)

    sprite.setPosition(position);
}

void Player::handleInput()
{
    // سرعت افقی صفر می‌شود تا اگر دکمه‌ای زده نشد، کاراکتر بایستد
    velocity.x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        velocity.x = -movementSpeed;
        sprite.setTexture(*texLeft); // تغییر تصویر به سمت چپ
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        velocity.x = movementSpeed;
        sprite.setTexture(*texRight); // تغییر تصویر به سمت راست
    }

    // پرش دستی برای تست (بعداً حذف می‌شود و به برخورد با سکوها متصل می‌شود)
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocity.y > 0.f) {
    //  jump();
    //}
}

void Player::update(float deltaTime, float windowWidth)
{
    // اعمال گرانش و سرعت
    velocity.y += gravity * deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;

    // پیچش صفحه (Screen Wrap)
    if (position.x < 0.f)
    {
        position.x = windowWidth;
    }
    else if (position.x > windowWidth)
    {
        position.x = 0.f;
    }

    sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Player::jump() { velocity.y = jumpForce; }
sf::Vector2f Player::getPosition() const { return position; }
sf::Vector2f Player::getVelocity() const { return velocity; }
void Player::setVelocity(sf::Vector2f vel) { velocity = vel; }
sf::FloatRect Player::getBounds() const { return sprite.getGlobalBounds(); }
int Player::getScore() const { return score; }

void Player::setPosition(sf::Vector2f pos)
{
    position = pos;
    sprite.setPosition(position);
}