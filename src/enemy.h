#pragma once

#include "SFML/Graphics/RectangleShape.hpp"
#include <SFML/Graphics.hpp>
#include "grid.h"

class Enemy : public Unit
{

public:
	sf::RectangleShape shape;
	Enemy();
	Enemy(std::shared_ptr<Grid> grid, double x, double y);
	Enemy(sf::RectangleShape shape);
	void draw(sf::RenderWindow &window) override;
};