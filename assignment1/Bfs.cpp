#include "search.h"
#include <queue>
#include <iostream>
using namespace std;

Coord Dir[5] = { Coord(-1, 0), Coord(1, 0), Coord(0, -1), Coord(0, 1),Coord(0, 0) };


vector<struct step> Bfs(Coord start, Coord goal, vector<int> sequences)
{
    //vector<struct step> solution;

    queue<struct state> que;
    struct state init;
    init.pos = start;
    init.dep = 0;
    init.solution.clear();
    que.push(init);

    while(!que.empty())
    {
        struct state current = que.front();
        que.pop();

        for(int i = 0; i < 5; i++)
        {
            struct state new_state;
            new_state.pos = current.pos + Dir[i] * sequences[current.dep];
            new_state.solution.assign(current.solution.begin(), current.solution.end());
            new_state.dep = current.dep + 1;
            struct step move;
            move.dir = i;
            move.cnt = sequences[current.dep];
            new_state.solution.push_back(move);
            if(new_state.pos == goal)
            {
                return new_state.solution;
            }
            else
            {
                que.push(new_state);
            }
        }
    }
}
