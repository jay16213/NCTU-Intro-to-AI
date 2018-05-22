#ifndef __FOREST_H__
#define __FOREST_H__

#include "TreeNode.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Forest {
public:
    Forest();
    Forest(int n_trees, int n_features, int n_attribute_bagging, double p_validations);
    ~Forest();

    void loadTrainingSample(const string training_file);
    void train();
    int classify(Data data);

    int n_samples;
    vector<Data> training_sample;
    vector<Data> training_data;
    vector<Data> validation_data;
    vector<string> class_name;

private:
    void chooseValidationData(unsigned int size);
    vector<Data> randomSubset(unsigned int size);

    int n_trees;
    int n_features;
    int n_attribute_bagging;
    double p_validations;
    vector<TreeNode*> trees;
};

void sumUp(vector<double> dest, vector<double> src);
int findLabel(string label, vector<string> class_name);
int predictClass(vector<double> distributions);

#endif
