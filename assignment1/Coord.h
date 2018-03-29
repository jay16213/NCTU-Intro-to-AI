#ifndef _COORD_H_
#define _COORD_H_

// define X-Y coordinate class
class Coord {
public:
    Coord();
    Coord(int x, int y);
    ~Coord();

    Coord operator+ (const Coord rhs) const;
    Coord operator* (const int scalar) const;
    Coord operator= (const Coord rhs);
    Coord operator+= (const Coord rhs);
    bool operator== (const Coord rhs);

    int x;
    int y;
};
#endif
