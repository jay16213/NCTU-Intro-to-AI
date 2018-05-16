#ifndef __FOREST_H__
#define __FOREST_H__

#include "TreeNode.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

class Forest {
protected:
    int n_trees;
    int n_features;
    vector<TreeNode> trees;
    vector<string> classes;
    vector<Data> randomSubset(unsigned int size);
public:
    Forest();
    Forest(int n_trees, int n_features);
    ~Forest();

    void loadTrainingData(const char *training_file, int number_of_attributes);
    void train();
    int classify(Data data);
    
    vector<Data> training_data;
};

void sumUp(vector<double> dest, vector<double> src);
int findLabel(string label, vector<string> classes);
int predictClass(vector<double> distributions);
#endif
