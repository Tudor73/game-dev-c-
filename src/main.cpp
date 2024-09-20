#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "enemy.h"
#include "player.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <iostream>
#include <random>
#include "globals.h"
#include "grid.h"
#include <memory>

int WIDTH = 800;
int HEIGHT = 800;
const int ENEMIES_PER_WAVE = 4;

std::shared_ptr<Grid> grid = std::make_shared<Grid>();

bool IsMouseOver(sf::CircleShape shape, sf::RenderWindow *window)
{
	sf::Vector2i localPosition = sf::Mouse::getPosition(*window);

	if (localPosition.x >= shape.getPosition().x &&
		localPosition.x <= shape.getPosition().x + 2 * shape.getRadius() &&
		localPosition.y >= shape.getPosition().y &&
		localPosition.y <= shape.getPosition().y + 2 * shape.getRadius())
	{
		return true;
	}

	return false;
}

sf::Vector2i posInsideWindow(sf::Vector2i pos)
{
	sf::Vector2i newPos;
	if (pos.x <= 0)
	{
		newPos.x = 0;
	}
	else if (pos.x >= WIDTH)
	{
		newPos.x = WIDTH;
	}
	else
	{
		newPos.x = pos.x;
	}
	if (pos.y >= HEIGHT)
	{
		newPos.y = HEIGHT;
	}
	else if (pos.y <= 0)
	{
		newPos.y = 0;
	}
	else
	{
		newPos.y = pos.y;
	}
	return newPos;
}

void SpawnEnemies(int nr)
{
	const int intervalSize = HEIGHT / nr;
	std::random_device rd;
	std::mt19937 gen(rd());
	for (std::size_t i = 0; i < nr - 1; i++)
	{
		std::uniform_real_distribution<double> dis(i * intervalSize,
												   (i + 1) * intervalSize - 50);
		auto y = dis(gen);
		std::shared_ptr<Enemy> e = std::make_shared<Enemy>(grid, 0.f, y);
		grid->add(e);
	}
}

void moveEnemies()
{
	for (size_t i = 0; i < Grid::NUM_CELLS; i++)
	{
		for (size_t j = 0; j < Grid::NUM_CELLS; j++)
		{
			for (auto u : grid->cells[i][j])
			{
				Enemy *e = dynamic_cast<Enemy *>(u.get());
				if (e)
				{
					e->move(e->x + 1.f, e->y);
				}
			}
		}
	}
}

void moveBullets(std::shared_ptr<Player> p)
{
	for (auto &bullet : p.get()->bullets)
	{

		auto angle = bullet.second;
		bullet.first.move(4 * cos(angle), 4 * sin(angle));
	}
}

int main()
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML shapes",
							sf::Style::Default, settings);

	window.setVerticalSyncEnabled(true);
	bool isButtonPressed = false;
	std::shared_ptr<Player> player = std::make_shared<Player>(grid);
	grid->add(player);
	sf::Clock clock;

	bool w_key, a_key, s_key, d_key = false;
	while (window.isOpen())
	{
		// Process events
		sf::Event event;

		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed)
			{
				switch (event.key.code)
				{
				case sf::Keyboard::W:
					w_key = true;
					break;
				case sf::Keyboard::A:
					a_key = true;
					break;
				case sf::Keyboard::S:
					s_key = true;
					break;
				case sf::Keyboard::D:
					d_key = true;
					break;
				default:
					break;
				}
			}
			if (event.type == sf::Event::MouseMoved)
			{
				double angle = atan2(sf::Mouse::getPosition(window).y - player->gun.getPosition().y, sf::Mouse::getPosition(window).x - player->gun.getPosition().x) * 180 / M_PI;
				player->Rotate(angle + 90);
			}

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					double angle = atan2(sf::Mouse::getPosition(window).y - player->gun.getPosition().y, sf::Mouse::getPosition(window).x - player->gun.getPosition().x);
					player->Shoot(angle);
				}
			}
		}

		if (clock.getElapsedTime() >= sf::seconds(1))
		{
			SpawnEnemies(ENEMIES_PER_WAVE);
			clock.restart();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			player->Move(0.f, -1.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			player->Move(-1.f, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			player->Move(0.f, 1.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			player->Move(1.f, 0.f);
		}

		moveEnemies();
		moveBullets(player);

		window.clear();
		for (size_t i = 0; i < Grid::NUM_CELLS; i++)
		{
			for (size_t j = 0; j < Grid::NUM_CELLS; j++)
			{
				for (auto u : grid->cells[i][j])
				{
					u->draw(window);
				}
			}
		}

		for (auto &b : player->bullets)
		{
			window.draw(b.first);
		}
		window.display();
	}
	return 0;
}
