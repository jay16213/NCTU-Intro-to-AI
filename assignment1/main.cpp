#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdio>
#include <string>
#include <vector>
#include "search.h"
#include "Coord.h"
using namespace std;

void print_solution(vector<struct movement> sol);

//record the number of nodes that a search algorithm expanded
int node_expanded;

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Usage: ./main <input filename>\n");
        exit(0);
    }

    ifstream in(argv[1]);

    string line;
    while(getline(in, line))
    {
        stringstream ss(line);

        string method;
        Coord goal;
        vector<int> sequences;

        ss >> method >> goal.x >> goal.y;

        int integer;
        while(ss >> integer) sequences.push_back(integer);


        vector<struct movement> sol;  // the solution
        node_expanded = 0;

        // Search the solution according to input method
        if(method == "BFS")
            sol = Bfs(Coord(0, 0), goal, sequences);
        else if(method == "IDS")
            sol = Ids(Coord(0, 0), goal, sequences);
        else if(method == "A*")
            sol = Astar(Coord(0, 0), goal, sequences);

        // Output message
        printf("========================================\n");
        printf("method: %s\n", method.c_str());
        printf("goal: (%d, %d)\n", goal.x, goal.y);
        printf("node has expanded: %d\n", node_expanded);
        print_solution(sol);
    }

    in.close();
    return 0;
}

void print_solution(vector<struct movement> sol)
{
    if(sol.empty())
    {
        printf("No solution!\n");
        return;
    }

    Coord pos(0, 0);
    printf("initial    (0, 0)\n");
    for(int i = 0; i < sol.size(); i++)
    {
        switch(sol[i].direction)
        {
            case LEFT:
                pos += Coord(-1, 0) * sol[i].steps;
                printf("(x-) %3d   (%2d, %2d)\n", sol[i].steps, pos.x, pos.y);
                break;

            case RIGHT:
                pos += Coord(1, 0) * sol[i].steps;
                printf("(x+) %3d   (%d, %d)\n", sol[i].steps, pos.x, pos.y);
                break;

            case UP:
                pos += Coord(0, -1) * sol[i].steps;
                printf("(y-) %3d   (%d, %d)\n", sol[i].steps, pos.x, pos.y);
                break;

            case DOWN:
                pos += Coord(0, 1) * sol[i].steps;
                printf("(y+) %3d   (%d, %d)\n", sol[i].steps, pos.x, pos.y);
                break;

            default:
                printf("(S) %4d   (%d, %d)\n", sol[i].steps, pos.x, pos.y);
                break;
        }
    }

    return;
}
