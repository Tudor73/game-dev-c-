#pragma once
#include <string>
#include "SFML/Graphics/CircleShape.hpp"
#include <SFML/Graphics.hpp>
#include "globals.h"
class Player
{
public:
	int name;
	sf::CircleShape shape;
	sf::RectangleShape gun;
	std::vector<std::pair<sf::CircleShape, double>> bullets;
	float gunAngle;
	Player();

	std::string PlayerToString();
	void Move(float offsetX, float offsetY);
	void DrawPlayer(sf::RenderWindow &window);
	void Rotate(float angle);
	void Shoot(double angle);
};