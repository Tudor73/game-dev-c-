#include "enemy.h"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

Enemy::Enemy() {
    sf::RectangleShape defaultShape((sf::Vector2<float>(30.f, 30.f)));
    defaultShape.setFillColor(sf::Color::Red);
    this->shape = defaultShape;
}

Enemy::Enemy(sf::RectangleShape shape) { this->shape = shape; }