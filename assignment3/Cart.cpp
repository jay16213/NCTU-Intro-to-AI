#include "Cart.hpp"
using namespace std;

Cart::Cart(int id)
{
    tree_id = id;
    root = new TreeNode;
}
Cart::~Cart()
{
    delete root;
}

void Cart::loadTrainingData(const char *training_file, int num_of_features)
{
    ifstream fin(training_file);
    this->num_of_features = num_of_features;

    map<string, int> label_tab;
    int label_id = 0;
    string line;
    while(getline(fin, line))
    {
        stringstream ss(line);
        Data data;
        for(int i = 0; i < num_of_features; i++)
        {
            Attribute tmp;
            tmp.id = i;
            ss >> tmp.value;
            data.feature.push_back(tmp);
        }

        string label_str;
        ss >> label_str;

        if(label_tab.find(label_str) == label_tab.end())
            label_tab.insert(pair<string, int>(label_str, label_id));

        data.label.id = label_tab[label_str];
        data.label.str = label_str;
        training_data.push_back(data);
    }

    // for(auto data : training_data_)
    // {
    //     printf("%f %f %s\n", data.attributes[0], data.attributes[1], data.label.c_str());
    // }

    fin.close();
    return;
}

void Cart::learn()
{
    return;
}
