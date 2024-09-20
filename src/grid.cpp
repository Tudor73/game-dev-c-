
#include "grid.h"
Unit::Unit()
{
}

Unit::Unit(std::shared_ptr<Grid> grid, double x, double y)
{
    this->grid = grid;
    this->x = x;
    this->y = y;
}

void Unit::move(double x, double y)
{
    this->x = x;
    this->y = y;
    grid->move(shared_from_this(), x, y);
}

Grid::Grid()
{
    // Clear the grid.
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
            cells[x][y] = std::vector<std::shared_ptr<Unit>>{};
    }
}

void Grid::add(std::shared_ptr<Unit> unit)
{
    double x = unit->x;
    double y = unit->y;

    int cell_x = (int)(x / Grid::CELL_SIZE);
    int cell_y = (int)(y / Grid::CELL_SIZE);

    if (cell_x < 0 || cell_x > Grid::NUM_CELLS)
        return;

    if (cell_y < 0 || cell_y > Grid::NUM_CELLS)
        return;

    std::cout << cells[cell_x][cell_y].size() << std::endl;
    cells[cell_x][cell_y]
        .push_back(unit);
}

void Grid::add(std::shared_ptr<Unit> unit, double x, double y)
{
    int cell_x = (int)(x / Grid::CELL_SIZE);
    int cell_y = (int)(y / Grid::CELL_SIZE);

    if (cell_x < 0 || cell_x > Grid::NUM_CELLS)
        return;

    if (cell_y < 0 || cell_y > Grid::NUM_CELLS)
        return;

    cells[cell_x][cell_y]
        .push_back(unit);
}

void Grid::move(std::shared_ptr<Unit> unit, double newPosX, double newPosY)
{
    int oldCellX = (int)(unit->x / Grid::CELL_SIZE);
    int oldCellY = (int)(unit->y / Grid::CELL_SIZE);

    int cellX = (int)(newPosX / Grid::CELL_SIZE);
    int cellY = (int)(newPosY / Grid::CELL_SIZE);

    if (oldCellX == cellX && oldCellY == cellY)
    {
        return;
    }
    unit->x = newPosX;
    unit->y = newPosY;
    cells[cellX][cellY]
        .erase(std::remove(cells[cellX][cellY].begin(), cells[cellX][cellY].end(), unit), cells[cellX][cellY].end());
    add(unit, newPosX, newPosY);
}

void Grid::handleColisions()
{
    for (int x = 0; x < NUM_CELLS; x++)
    {
        for (int y = 0; y < NUM_CELLS; y++)
        {
            handleCell(cells[x][y]);
        }
    }
}

void Grid::handleCell(std::vector<std::shared_ptr<Unit>> cell)
{
    for (size_t i = 0; i < cell.size() - 1; i++)
    {
        for (size_t j = i + 1; j < cell.size(); j++)
        {
            if (cell[i]->x == cell[j]->x || cell[i]->y == cell[j]->y)
            {
                std::cout << "same x !!!" << std::endl;
            }
        }
    }
}
