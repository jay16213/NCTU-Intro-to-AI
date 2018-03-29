#include "search.h"
#include <stack>
#include <cstdio>

bool Ids(Coord start, Coord goal, vector<int> sequences, vector<struct movement> &solution, int limit, int depth)
{
    if(depth >= limit) return false;

    bool has_sol = false;
    for(int i = 0; i < 5; i++)
    {
        struct movement move;
        move.direction = i;
        move.steps = sequences[depth];

        Coord go_to  = start + Dir[i] * move.steps;
        solution.push_back(move);

        if(go_to == goal)
            return true;
        else
            has_sol = Ids(go_to, goal, sequences, solution, limit, depth + 1);

        if(has_sol) break;
        solution.pop_back();
    }

    return has_sol;
}
