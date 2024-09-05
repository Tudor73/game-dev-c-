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

const int WIDTH = 800;
const int HEIGHT = 600;
const int ENEMIES_PER_WAVE = 4;

bool IsMouseOver(sf::CircleShape shape, sf::RenderWindow *window) {
    sf::Vector2i localPosition = sf::Mouse::getPosition(*window);

    if (localPosition.x >= shape.getPosition().x &&
        localPosition.x <= shape.getPosition().x + 2 * shape.getRadius() &&
        localPosition.y >= shape.getPosition().y &&
        localPosition.y <= shape.getPosition().y + 2 * shape.getRadius()) {
        return true;
    }

    return false;
}

sf::Vector2i posInsideWindow(sf::Vector2i pos) {
    sf::Vector2i newPos;
    if (pos.x <= 0) {
        newPos.x = 0;
    } else if (pos.x >= WIDTH) {
        newPos.x = WIDTH;
    } else {
        newPos.x = pos.x;
    }
    if (pos.y >= HEIGHT) {
        newPos.y = HEIGHT;
    } else if (pos.y <= 0) {
        newPos.y = 0;
    } else {
        newPos.y = pos.y;
    }
    return newPos;
}

std::vector<Enemy> SpawnEnemies(int nr) {
    std::vector<Enemy> enemies;

    const int intervalSize = HEIGHT / nr;
    std::random_device rd;
    std::mt19937 gen(rd());
    for (std::size_t i = 0; i < nr - 1; i++) {
        Enemy e;
        std::uniform_real_distribution<double> dis(i * intervalSize,
                                                   (i + 1) * intervalSize - 50);
        auto y = dis(gen);
        e.shape.setPosition(0.f, y);
        enemies.push_back(e);
    }
    return enemies;
}

void moveEnemies(std::vector<Enemy> &enemies) {
    for (Enemy &e : enemies) {
        e.shape.move(1.f, 0.f);
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SFML shapes",
                            sf::Style::Default, settings);

    window.setVerticalSyncEnabled(true);
    bool isButtonPressed = false;
    sf::CircleShape circle(50.f);

    circle.setFillColor(sf::Color(100, 250, 50));
    circle.setRadius(20.f);
    circle.setPosition(static_cast<float>(WIDTH / 2),
                       static_cast<float>(HEIGHT / 2));

    std::vector<Enemy> enemies;
    sf::Clock clock;

    bool w_key, a_key, s_key, d_key = false;
    while (window.isOpen()) {
        // Process events
        sf::Event event;

        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                switch (event.key.code) {
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
        }

        if (clock.getElapsedTime() >= sf::seconds(1)) {
            auto enemyWave = SpawnEnemies(ENEMIES_PER_WAVE);
            enemies.insert(enemies.end(), enemyWave.begin(), enemyWave.end());
            clock.restart();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            circle.move(0.f, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            circle.move(-1.f, 0.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            circle.move(0.f, 1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            circle.move(1.f, 0.f);
        }

        moveEnemies(enemies);
        window.clear();
        for (const Enemy &e : enemies) {
            window.draw(e.shape);
        }
        window.draw(circle);
        window.display();
    }
    return 0;
}
