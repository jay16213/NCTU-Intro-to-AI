#ifndef __NODE_H__
#define __NODE_H__

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

struct Attribute {
    int id;
    double value;
};

struct Data {
    vector<Attribute> attributes;
    int class_id;
};

class TreeNode {
public:
    TreeNode();
    TreeNode(int num_of_attributes);
    ~TreeNode();

    void setNumOfAttributes(int value);
    void train(vector<Data> data, int n_classes, int dep);
    vector<double> classify(Data data);

private:
    vector<Data> randomSampling(const vector<Data> data);
    vector<double> extractAttribute(const vector<Data> data, int attribute_id);
    vector<double> computeThresholdValues(vector<double> attribute);
    void split(const vector<Data> src, Attribute threshold, vector<Data> &less, vector<Data> &greater);

    TreeNode *left_child;
    TreeNode *right_child;

    int num_of_attributes;
    Attribute threshold;
    vector<double> distribution;
};

vector<double> computePValue(const vector<Data> classes, int num_of_classes);
inline double giniImpurity(const vector<Data> classes, int num_of_classes);
inline double totalImpurity(const vector<Data> less, const vector<Data> greater, int num_of_classes);

#endif
