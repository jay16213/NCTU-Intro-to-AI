#include "search.h"
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

// record the number of nodes expanded
// initialize at main.cpp
extern int node_expanded;

#ifdef ORIGINAL_HEURISTIC
inline int heuristic(int dx, int dy)
{
    return floor(abs(dx) / 9.0) + floor(abs(dy) / 9.0);
}
#endif

#ifdef IMPROVE_HEURISTIC
inline int heuristic(int dx, int dy)
{
    return ceil(abs(dx) / 9.0) + ceil(abs(dy) / 9.0);
}
#endif

// the state of A*
struct stateA {
    vector<struct movement> solution;
    Coord position;
    int cost;
    int level;
};


// a compare function for priority queue
class myComp {
    Coord goal;

public:
    myComp(Coord goal) { this->goal = goal; }
    bool operator() (const struct stateA& lhs, const struct stateA& rhs) const
    {
        int total_cost_lhs = lhs.cost + heuristic(lhs.position.x - this->goal.x, lhs.position.y - this->goal.y);
        int total_cost_rhs = rhs.cost + heuristic(rhs.position.x - this->goal.x, rhs.position.y - this->goal.y);

        return total_cost_lhs > total_cost_rhs;
    }
};

typedef priority_queue<struct stateA, vector<struct stateA>, myComp> PQueue;

vector<struct movement> Astar(Coord start, Coord goal, vector<int> sequences)
{
    struct stateA init;
    init.position = start;
    init.level = 0;
    init.solution.clear();
    init.cost = 0;

    PQueue que(goal);
    que.push(init);

    while(!que.empty())
    {
        struct stateA current = que.top();
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

            struct stateA new_state;
            new_state.position = current.position + Direction_vec[i] * move.steps;
            new_state.level = current.level + 1;
            new_state.cost = current.cost + 1;
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
