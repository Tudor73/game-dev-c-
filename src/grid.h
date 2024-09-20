#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
class Grid;
class Unit : public std::enable_shared_from_this<Unit>
{
public:
    double x,
        y;
    std::shared_ptr<Grid> grid;

    Unit();
    Unit(std::shared_ptr<Grid> grid, double x, double y);
    void move(double x, double y);
    virtual void draw(sf::RenderWindow &window) = 0;
};

class Grid
{

public:
    static const int NUM_CELLS = 10;
    static const int CELL_SIZE = 80;
    std::vector<std::shared_ptr<Unit>> cells[NUM_CELLS][NUM_CELLS];

    Grid();
    void add(std::shared_ptr<Unit> unit);
    void add(std::shared_ptr<Unit> unit, double x, double y);
    void move(std::shared_ptr<Unit> unit, double new_pos_x, double new_pos_y);
    void handleColisions();
    void handleCell(std::vector<std::shared_ptr<Unit>> cell);
};
