#ifndef __NODE_H__
#define __NODE_H__

#include <vector>
#include <string>
using namespace std;

struct Label {
    int id;
    string str;
};

struct Attribute {
    int id;
    double value;
};

struct Data {
    vector<Attribute> feature;
    Label label;
};

class TreeNode {
public:
    TreeNode();
    ~TreeNode();

    void train();

private:

    void split(const vector<Data> src, Attribute threshold, vector<Data> &less, vector<Data> &greater);

    TreeNode *left_child;
    TreeNode *right_child;

    Attribute threshold;
};

double giniImpurity(const vector<Data> classes, int num_of_classes = 2);

#endif
