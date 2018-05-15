#include "TreeNode.hpp"
using namespace std;

TreeNode::TreeNode()
{
    left_child = NULL;
    right_child = NULL;
    threshold.id = -1;
    threshold.value = 0.0;
}

TreeNode::~TreeNode()
{
    if(left_child)
        delete left_child;
    if(right_child)
        delete right_child;
}

void TreeNode::split(const vector<Data> src, Attribute threshold, vector<Data> &less, vector<Data> &greater)
{
    less.clear();
    greater.clear();

    for(auto data : src)
    {
        if(data.feature[threshold.id].value <= threshold.value)
            less.push_back(data);
        else
            greater.push_back(data);
    }

    return;
}

void TreeNode::train()
{
    return;
}

vector<double> computePValue(const vector<Data> classes, int num_of_classes)
{
    vector<int> count(num_of_classes, 0);
    for(auto c : classes)
    {

        count[c.label.id]++;
    }


}

double giniImpurity(const vector<Data> classes, int num_of_classes)
{

    vector<double> p_values;

    double result = 1.0;

    for(auto p : p_values)
        result -= p*p;

    return result;
}
