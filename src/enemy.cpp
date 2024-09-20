#include "enemy.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

Enemy::Enemy()
{
    sf::RectangleShape defaultShape((sf::Vector2<float>(30.f, 30.f)));
    defaultShape.setFillColor(sf::Color::Red);
    this->shape = defaultShape;
}

Enemy::Enemy(std::shared_ptr<Grid> grid, double x, double y) : Unit(grid, x, y)
{
    sf::RectangleShape defaultShape((sf::Vector2<float>(30.f, 30.f)));
    defaultShape.setFillColor(sf::Color::Red);
    this->shape = defaultShape;
}

Enemy::Enemy(sf::RectangleShape shape) { this->shape = shape; }

void Enemy::draw(sf::RenderWindow &window)
{
    this->shape.setPosition(this->x, this->y);
    window.draw(this->shape);
}
