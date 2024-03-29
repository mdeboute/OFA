#include "Graph/Position.hpp"

#include <cmath>

Position::Position(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Position::getX() const
{
    return this->x;
}

int Position::getY() const
{
    return this->y;
}

// euclidian distance
double Position::dist(Position p) const
{
    int xDelta = this->x - p.getX();
    int yDelta = this->y - p.getY();
    return std::sqrt((xDelta * xDelta) + (yDelta * yDelta));
}