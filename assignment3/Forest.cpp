#include "Forest.hpp"
#include <iostream>
using namespace std;

Forest::Forest() {}

Forest::Forest(int n_trees, int n_features)
{
    this->n_trees = n_trees;
    this->n_features = n_features;
}

Forest::~Forest()
{
    for(auto tree : trees)
        delete tree;
}

void Forest::loadTrainingData(const char *training_file, int num_of_features)
{
    printf("Loading training data from %s\n", training_file);
    ifstream fin(training_file);
    this->n_features = num_of_features;

    int class_id = -1;
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
            data.attributes.push_back(tmp);
        }

        string class_str;
        ss >> class_str;

        if(findLabel(class_str, class_name) == -1)
        {
            class_name.push_back(class_str);
            class_id++;
        }

        data.class_id = class_id;
        training_data.push_back(data);
    }

    for(int i = 0; i < n_trees; i++)
        trees.push_back(new TreeNode(n_features));

    cout << "total data: " << training_data.size();
    cout << " attribute: " << n_features;
    cout << " classes: " << class_name.size() << endl;
    fin.close();
    return;
}

void Forest::train()
{
    printf("-----forest training-----\n");
    // 80-20 rule: 80% of data used to training
    int subset_size = (training_data.size() * 8) / 10;
    printf("tree bagging: training tree with %d elements\n", subset_size);

    for(int t= 0; t < n_trees; t++)
    {
        vector<Data> training_sample = randomSubset(subset_size);
        printf("training tree[%d]\n", t);
        trees[t]->train(training_sample, class_name.size(), 0);
    }

    printf("-----finish training-----\n");
    return;
}

vector<Data> Forest::randomSubset(unsigned int size)
{
    vector<Data> subset;

    for(int i = 0; i < size; i++)
    {
        int rand_index = rand() % training_data.size();
        subset.push_back(training_data[rand_index]);
    }

    return subset;
}

int Forest::classify(Data data)
{
    vector<int> class_vote(class_name.size(), 0);
    for(auto tree : trees)
    {
        vector<double> distributions = tree->classify(data);
        int predict = predictClass(distributions);
        assert(predict >= 0);
        assert(predict < class_vote.size());
        class_vote[predict]++;
    }

    int total_vote = 0;
    int max_vote = 0;
    int predict_class = -1;
    for(int i = 0; i < class_vote.size(); i++)
    {
        total_vote += class_vote[i];
        if(class_vote[i] > max_vote)
        {
            predict_class = i;
            max_vote = class_vote[i];
        }
    }

    // printf("predict: %s, prob: %lf, ", classes[predict_class].c_str(), (double) max_vote / total_vote);
    return predict_class;
}

int predictClass(vector<double> distributions)
{
    int max_dis = -1000000;
    int predicted_class = -1;
    for(int i = 0; i < distributions.size(); i++)
    {
        if(distributions[i] > max_dis)
        {
            max_dis = distributions[i];
            predicted_class = i;
        }
    }

    return predicted_class;
}

int findLabel(string label, vector<string> class_name)
{
    for(int i = 0; i < class_name.size(); i++)
    {
        if(class_name[i] == label)
            return i;
    }

    return -1;
}
