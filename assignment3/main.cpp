#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <cassert>
#include <vector>
#include <string>
#include <ctime>
#include <map>
#include "Forest.hpp"
using namespace std;

bool test(Forest *forest, Data test_data, vector<string> class_name)
{
    int predict_class = forest->classify(test_data);
    int expected_class = test_data.class_id;
    // cout << "predict: " << class_name[predict_class];
    // cout << " expected: " << class_name[expected_class] << endl;

    return predict_class == expected_class;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    int n_trees = 16;
    int n_features = 1;
    int n_attribute_bagging = 1;
    string training_file;
    int c;
    // TODO: validation subset size option, min impurity option
    while((c = getopt(argc, argv, "t:n:f:a:")) != -1)
    {
        switch(c)
        {
            case 't':
                training_file = optarg;
                break;
            case 'n':
                n_trees = atoi(optarg);
                assert(n_trees > 0);
                break;
            case 'f':
                n_features = atoi(optarg);
                assert(n_features > 0);
                break;

            case 'a':
                n_attribute_bagging = atoi(optarg);
                assert(n_attribute_bagging > 0);
            default:
                exit(1);
        }
    }

    Forest forest(n_trees, n_features);
    forest.loadTrainingSample(training_file, n_features);
    forest.train();

    int training_data_right = 0;
    int validation_data_right = 0;
    int training_data_size = forest.training_data.size();
    int validation_data_size = forest.validation_data.size();
    for(int i = 0; i < training_data_size; i++)
    {
        if(test(&forest, forest.training_data[i], forest.class_name))
            training_data_right++;
    }

    for(int i = 0; i < validation_data_size; i++)
    {
        if(test(&forest, forest.validation_data[i], forest.class_name))
            validation_data_right++;
    }

    printf("============================================\n");
    printf(" total test data: %d (%d for training, %d for validation)\n", forest.n_samples, training_data_size, validation_data_size);
    printf(" training: %lf, validation: %lf\n", (double) training_data_right / training_data_size, (double) validation_data_right / validation_data_size);
    printf("============================================\n");
    return 0;
}
