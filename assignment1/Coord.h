#ifndef _COORD_H_
#define _COORD_H_

class Coord {
public:
    Coord();
    Coord(int x, int y);
    ~Coord();

    Coord operator+ (const Coord rhs);
    Coord operator* (const int scalar);
    Coord operator= (const Coord rhs);
    Coord operator+= (const Coord rhs);
    bool operator== (const Coord rhs);

    int x;
    int y;
};
#endif
