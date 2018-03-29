#ifndef _SEARCH_H_
#define _SEARCH_H_

#include <vector>
#include "Coord.h"
using namespace std;

#define LEFT  0
#define RIGHT 1
#define UP    2
#define DOWN  3
#define SKIP  4

//
struct movement {
    int direction;                          // the move direction
    int steps;                              // number of steps this movement moves
};

// A state is a node on the search tree, stored the infofmation we need
struct state {
    vector<struct movement> solution;       // a possible solution path
    Coord position;                         // current position
    int level;                              // the level of the state
};

// 5 choice at each node
const Coord Dir[5] = {
    Coord(-1, 0),       // left
    Coord(1, 0),        // right
    Coord(0, -1),       // up
    Coord(0, 1),        // down
    Coord(0, 0)         // skip
};


// 3 search algorithms
vector<struct movement> Bfs(Coord start, Coord goal, vector<int> sequences);
bool Ids(Coord start, Coord goal, vector<int> sequences, vector<struct movement> &solution, int limit, int depth);
vector<struct movement> Astar(Coord start, Coord goal, vector<int> sequences);

#endif
