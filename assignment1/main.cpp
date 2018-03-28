#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Coord.h"
#include "search.h"
using namespace std;

void printSolution(vector<struct step> sol)
{
    Coord pos(0, 0);
    printf("initial    (0, 0)\n");
    for(int i = 0; i < sol.size(); i++)
    {
        if(sol[i].dir == LEFT)
        {
            pos += Coord(-1, 0) * sol[i].cnt;
            printf("(x-) %3d   (%2d, %2d)\n", sol[i].cnt, pos.x, pos.y);
        }
        else if(sol[i].dir == RIGHT)
        {
            pos += Coord(1, 0) * sol[i].cnt;
            printf("(x+) %3d   (%d, %d)\n", sol[i].cnt, pos.x, pos.y);
        }
        else if(sol[i].dir == UP)
        {
            pos += Coord(0, -1) * sol[i].cnt;
            printf("(y-) %3d   (%d, %d)\n", sol[i].cnt, pos.x, pos.y);
        }
        else if(sol[i].dir == DOWN)
        {
            pos += Coord(0, 1) * sol[i].cnt;
            printf("(y+) %3d   (%d, %d)\n", sol[i].cnt, pos.x, pos.y);
        }
        else
        {
            printf("(S) %4d   (%d, %d)\n", sol[i].cnt, pos.x, pos.y);
        }
    }

    return;
}

int main()
{
    ifstream in("input.txt");

    string line;
    while(getline(in, line))
    {
        stringstream ss(line);
        string method;
        Coord goal;
        ss >> method >> goal.x >> goal.y;

        printf("========================================\n");
        cout << method << endl;
        printf("goal: (%d, %d)\n", goal.x, goal.y);

        vector<int> sequences;
        int integer;
        while(ss >> integer) sequences.push_back(integer);

        vector<struct step> sol;
        if(method == "BFS")
        {
            sol = Bfs(Coord(0, 0), goal, sequences);
        }
        else if(method == "IDS")
        {
            sol = Ids(Coord(0, 0), goal, sequences);
        }
        else if(method == "A*")
        {
            sol = Astar(Coord(0, 0), goal, sequences);
        }

        printSolution(sol);
    }

    in.close();
    return 0;
}
