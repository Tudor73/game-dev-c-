#pragma once
#include <string>
#include "SFML/Graphics/CircleShape.hpp"
#include <SFML/Graphics.hpp>
#include "globals.h"
#include "grid.h"

class Player : public Unit
{
public:
	int name;
	sf::CircleShape shape;
	sf::RectangleShape gun;
	std::vector<std::pair<sf::CircleShape, double>> bullets;
	float gunAngle;
	Player(std::shared_ptr<Grid> grid);

	std::string PlayerToString();
	void Move(float offsetX, float offsetY);
	void draw(sf::RenderWindow &window) override;
	void Rotate(float angle);
	void Shoot(double angle);
};