#include "Coord.h"

Coord::Coord()
{
    this->x = 0;
    this->y = 0;
}

Coord::Coord(int x, int y)
{
    this->x = x;
    this->y = y;
}

Coord::~Coord() {}

Coord Coord::operator+ (const Coord rhs) const
{
    return Coord(this->x + rhs.x, this->y + rhs.y);
}

Coord Coord::operator* (const int scalar) const
{
    return Coord(this->x * scalar, this->y * scalar);
}

Coord Coord::operator= (const Coord rhs)
{
    this->x = rhs.x;
    this->y = rhs.y;
    return *this;
}

Coord Coord::operator+= (const Coord rhs)
{
    this->x += rhs.x;
    this->y += rhs.y;
    return *this;
}

bool Coord::operator== (const Coord rhs)
{
    return (this->x == rhs.x) && (this->y == rhs.y);
}
