#ifndef __CART_H__
#define __CART_H__

#include <algorithm>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include "TreeNode.hpp"
using namespace std;


class Cart {
public:
    Cart(int id = 0);
    ~Cart();

    void loadTrainingData(const char *training_file, int number_of_attributes);
    void learn();

    int tree_id;

private:

    int num_of_features;
    vector<Data> training_data;
    TreeNode *root;
};

#endif
