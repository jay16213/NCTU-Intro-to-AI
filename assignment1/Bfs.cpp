#include <iostream>
#include <queue>
#include "search.h"
using namespace std;

// record the number of nodes expanded
// initialize at main.cpp
extern int node_expanded;

vector<struct movement> Bfs(Coord start, Coord goal, vector<int> sequences)
{
    queue<struct state> que;

    // initialization
    struct state init_state;
    init_state.position = start;
    init_state.level = 0;

    que.push(init_state);

    while(!que.empty())
    {
        struct state current = que.front();
        que.pop();

        //no solution
        if(current.level >= sequences.size())
            return vector<struct movement>();

        node_expanded++;

        // 5 choices at each state: left, right, up, down, skip
        for(int i = 0; i < 5; i++)
        {
            struct movement move;
            move.direction = i;
            move.steps = sequences[current.level];

            struct state new_state;
            new_state.position = current.position + Dir[i] * move.steps;
            new_state.level = current.level + 1;
            new_state.solution.assign(current.solution.begin(), current.solution.end());
            new_state.solution.push_back(move);

            // If we find a solution, return the solution
            // Otherwise, push new_state to the queue and continue searching
            if(new_state.position == goal)
                return new_state.solution;
            else
                que.push(new_state);
        }
    }
}
