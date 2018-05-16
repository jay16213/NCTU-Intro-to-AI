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
    Forest(int n_trees, int n_features);
    ~Forest();

    void loadTrainingData(const char *training_file, int number_of_attributes);
    void train();
    int classify(Data data);

    vector<Data> training_data;

private:
    vector<Data> randomSubset(unsigned int size);

    int n_trees;
    int n_features;
    vector<TreeNode*> trees;
    vector<string> class_name;
};

void sumUp(vector<double> dest, vector<double> src);
int findLabel(string label, vector<string> class_name);
int predictClass(vector<double> distributions);

#endif