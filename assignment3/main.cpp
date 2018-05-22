#include <iostream>
#include <unistd.h>
#include <cassert>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <string>
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

void helpMsg()
{
    printf("Usage: ./random_forest -t <training_file> -f <number of attributes> [options]\n");
    printf("Options: \n");
    printf("    -n: number of trees the random forest use (default: 16)\n");
    printf("    -f: number of attributes the training set has\n");
    printf("    -a: number of attributes each node will bagging while training\n");
    printf("    -s: proportion of the validation data you want to use (default: 0.2)\n");
    return;
}

int main(int argc, char **argv)
{
    srand(time(NULL));

    int n_trees = 16;
    int n_features = -1;
    int n_attribute_bagging = 1;
    double p_validations = 0.2;
    string training_file = "";
    int c;
    // TODO: validation subset size option, min impurity option
    while((c = getopt(argc, argv, "t:n:f:a:s:h")) != -1)
    {
        switch(c)
        {
            case 'h':
                helpMsg();
                exit(0);
                break;
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
                break;
            case 's':
                p_validations = atof(optarg);
                assert(p_validations > 0.0);
                break;
            default:
                exit(1);
        }
    }

    if(training_file == "" || n_features == -1)
    {
        helpMsg();
        exit(0);
    }

    printf("pid: %d\n", getpid());

    Forest forest(n_trees, n_features, n_attribute_bagging, p_validations);
    forest.loadTrainingSample(training_file);
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
