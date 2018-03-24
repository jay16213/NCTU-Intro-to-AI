#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>
#include "Coord.h"
using namespace std;

vector<struct step> Bfs(Coord start, Coord goal, vector<int> sequences);
// void Ids(Coord start, Coord goal, vector<int> sequences);
// void Astar(Coord start, Coord goal, vector<int> sequences);

struct step {
    int dir;
    int cnt;
};

struct state {
    vector<struct step> solution;
    int dep;
    Coord pos;
};

#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3
#define SKIP  4

#endif
