#include "search.h"
#include <stack>

extern Coord Dir[5];

vector<struct step> Ids(Coord start, Coord goal, vector<int> sequences)
{
    for(int limit = 0;;limit++)
    {
        stack<struct state> tree;
        struct state init;
        init.pos = start;
        init.dep = 0;
        init.solution.clear();
        tree.push(init);

        while(!tree.empty())
        {
            struct state current = tree.top();
            tree.pop();

            int depth = current.dep + 1;
            if(depth >= limit) continue;

            for(int i = 0; i < 5; i++)
            {
                struct state new_state;
                new_state.pos = current.pos + Dir[i] * sequences[current.dep];
                new_state.solution.assign(current.solution.begin(), current.solution.end());
                new_state.dep = depth;
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
                    tree.push(new_state);
                }
            }
        }
    }
}
