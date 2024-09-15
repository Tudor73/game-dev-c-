#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
class Enemy
{

public:
	sf::RectangleShape shape;
	Enemy();
	Enemy(sf::RectangleShape shape);
};