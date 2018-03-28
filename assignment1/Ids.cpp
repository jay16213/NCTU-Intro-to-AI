#include "search.h"
#include <stack>

vector<struct movement> Ids(Coord start, Coord goal, vector<int> sequences)
{
    for(int limit = 0;;limit++)
    {
        stack<struct state> tree;
        struct state init;
        init.position = start;
        init.level = 0;

        tree.push(init);

        while(!tree.empty())
        {
            struct state current = tree.top();
            tree.pop();

            int depth = current.level + 1;
            if(depth >= limit) continue;

            for(int i = 0; i < 5; i++)
            {
                struct state new_state;
                new_state.position = current.position + Dir[i] * sequences[current.level];
                new_state.solution.assign(current.solution.begin(), current.solution.end());
                new_state.level = depth;
                struct movement move;
                move.direction = i;
                move.steps = sequences[current.level];
                new_state.solution.push_back(move);

                if(new_state.position == goal)
                    return new_state.solution;
                else
                    tree.push(new_state);
            }
        }
    }
}
