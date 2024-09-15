#include "player.h"

Player::Player()
{
    sf::CircleShape circle(50.f);

    circle.setFillColor(sf::Color(100, 250, 50));
    circle.setRadius(20.f);
    circle.setPosition(static_cast<float>(WIDTH / 2),
                       static_cast<float>(HEIGHT / 2));
    this->shape = circle;

    sf::RectangleShape rec(sf::Vector2f(10.f, 25.f));
    rec.setPosition(static_cast<float>(WIDTH / 2) + circle.getRadius(),
                    static_cast<float>(HEIGHT / 2) + circle.getRadius());
    this->gun = rec;
}

std::string Player::PlayerToString()
{
    return std::to_string(this->name);
}

void Player::Move(float offsetX, float offsetY)
{
    this->shape.move(offsetX, offsetY);
    this->gun.move(offsetX, offsetY);
}

void Player::DrawPlayer(sf::RenderWindow &window)
{
    window.draw(this->shape);
    window.draw(this->gun);
}

void Player::Rotate(float angle)
{
    this->gun.setOrigin(10.f / 2, 25.f);
    this->gun.setRotation(angle);
}

void Player::Shoot(double angle)
{
    auto bullet = sf::CircleShape(5.f);
    bullet.setPosition(this->gun.getPosition().x + 5.f / 2, this->gun.getPosition().y);
    this->bullets.push_back(std::pair<sf::CircleShape, double>(bullet, angle));
}
