#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>
#include "Coord.h"
using namespace std;

vector<struct step> Bfs(Coord start, Coord goal, vector<int> sequences);
vector<struct step> Ids(Coord start, Coord goal, vector<int> sequences);
vector<struct step> Astar(Coord start, Coord goal, vector<int> sequences);

struct step {
    int dir;
    int cnt;
};

struct state {
    vector<struct step> solution;
    int dep;
    Coord pos;
};

extern Coord Dir[5];

#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3
#define SKIP  4

#endif
