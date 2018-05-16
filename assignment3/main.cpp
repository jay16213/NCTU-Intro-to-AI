#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include "Forest.hpp"
using namespace std;

bool test(Forest *forest, Data test_data, vector<string> classes)
{
    int predict_class = forest->classify(test_data);
    int expected_class = test_data.label.id;
    if(predict_class == expected_class)
    {
        printf("predict: %d, expected: %d\n", predict_class, expected_class);
        return true;
    }

    return false;
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    if(argc < 4)
    {
        printf("Usage: ./main <train_file> <number of attributes> <number of trees>\n");
        exit(0);
    }

    Forest forest(atoi(argv[3]), atoi(argv[2]));
    forest.loadTrainingData(argv[1], atoi(argv[2]));
    forest.train();

    int right = 0;
    int total = forest.training_data.size();
    for(int i = 0; i < forest.training_data.size(); i++)
    {
        int p = forest.classify(forest.training_data[i]);
        // printf("expected: %s\n", forest.training_data[i].label.str.c_str());
        if(p == forest.training_data[i].label.id)
            right++;
    }

    printf("total: %d, right: %d, accurate: %lf\n", total, right, (double) right / total);
    return 0;
}
