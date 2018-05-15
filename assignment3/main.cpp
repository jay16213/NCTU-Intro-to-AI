#include <fstream>
#include <sstream>
#include <cstdio>
#include <vector>
#include <string>
#include "Cart.hpp"
using namespace std;

int main(int argc, char **argv)
{
    if(argc < 3)
    {
        printf("Usage: ./main <train_file> <number of attributes>\n");
        exit(0);
    }

    Cart cart;
    cart.loadTrainingData(argv[1], atoi(argv[2]));

    return 0;
}
