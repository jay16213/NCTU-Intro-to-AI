#include <cstdio>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Coord.h"
#include "search.h"
using namespace std;

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

        cout << method << endl;
        printf("goal: (%d, %d)\n", goal.x, goal.y);

        vector<int> sequences;
        int integer;
        while(ss >> integer) sequences.push_back(integer);

        if(method == "BFS")
        {
            vector<struct step> sol = Bfs(Coord(0, 0), goal, sequences);
            printf("initial    (0, 0)\n");
            Coord pos(0, 0);
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
                    printf("(S) %d   (%d, %d)\n", sol[i].cnt, pos.x, pos.y);
                }
            }
        }
        else
        {

        }
    }

    in.close();
    return 0;
}
