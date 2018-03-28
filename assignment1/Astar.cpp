#include "search.h"
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cmath>
using namespace std;

extern Coord Dir[5];

inline int heuristic(int dx, int dy)
{
    return floor(abs(dx) / 9.0) + floor(abs(dy) / 9.0);
}

struct stateA {
    vector<struct step> solution;
    Coord pos;
    int cost;
    int dep;
};

class myComp {
    Coord goal;

public:
    myComp(Coord goal) { this->goal = goal; }
    bool operator() (const struct stateA& lhs, const struct stateA& rhs) const
    {
        int total_cost_lhs = lhs.cost + heuristic(lhs.pos.x - this->goal.x, lhs.pos.y - this->goal.y);
        int total_cost_rhs = rhs.cost + heuristic(rhs.pos.x - this->goal.x, rhs.pos.y - this->goal.y);

        return total_cost_lhs > total_cost_rhs;
    }
};

typedef priority_queue<struct stateA, vector<struct stateA>, myComp> PQueue;

vector<struct step> Astar(Coord start, Coord goal, vector<int> sequences)
{
    struct stateA init;
    init.pos = start;
    init.dep = 0;
    init.solution.clear();
    init.cost = 0;

    PQueue que(goal);
    que.push(init);

    while(!que.empty())
    {
        struct stateA current = que.top();
        que.pop();

        for(int i = 0; i < 5; i++)
        {
            struct stateA new_state;
            new_state.pos = current.pos + Dir[i] * sequences[current.dep];
            new_state.solution.assign(current.solution.begin(), current.solution.end());
            new_state.dep = current.dep + 1;

            struct step move;
            move.dir = i;
            move.cnt = sequences[current.dep];
            new_state.solution.push_back(move);

            new_state.cost = current.cost + 1;

            if(new_state.pos == goal)
                return new_state.solution;
            else
                que.push(new_state);
        }
    }
}
