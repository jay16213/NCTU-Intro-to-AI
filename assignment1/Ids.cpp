#include "search.h"
#include <stack>
#include <cstdio>

// record the number of nodes expanded
// initialize at main.cpp
extern int node_expanded;

vector<struct movement> Ids(Coord start, Coord goal, vector<int> sequences)
{
    vector<struct movement> sol;
    for(int limit = 1; limit <= sequences.size(); limit++)
    {
        // If find the solution, return
        // Otherwise increase the limit depth & keep searching
        if(Dls(start, goal, sequences, sol, limit, 0))
            break;
    }

    return sol;
}

// Depth-limited searching
bool Dls(Coord start, Coord goal, vector<int> sequences, vector<struct movement> &solution, int limit, int depth)
{
    if(depth >= limit) return false;

    node_expanded++;

    bool has_sol = false;

    // 5 options can be choosed: move left, right, up, down, or skip
    for(int i = 0; i < 5; i++)
    {
        struct movement move;
        move.direction = i;
        move.steps = sequences[depth];

        Coord go_to  = start + Direction_vec[i] * move.steps;
        solution.push_back(move);

        // If we find a solution, return
        // Otherwise, keep searching until reach the depth limit
        if(go_to == goal)
            return true;
        else
            has_sol = Dls(go_to, goal, sequences, solution, limit, depth + 1);

        if(has_sol) break; // if has find a solution, return immediately
        solution.pop_back();
    }

    return has_sol;
}
