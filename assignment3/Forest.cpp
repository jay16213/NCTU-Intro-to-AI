#include "Forest.hpp"
#include <iostream>
#include <cmath>
using namespace std;

Forest::Forest() {}

Forest::Forest(int n_trees, int n_features, int n_attribute_bagging, double p_validations)
{
    this->n_trees = n_trees;
    this->n_features = n_features;
    this->n_attribute_bagging = n_attribute_bagging;
    this->p_validations = p_validations;

    for(int i = 0; i < n_trees; i++)
        trees.push_back(new TreeNode(n_features));
}

Forest::~Forest()
{
    for(auto tree : trees)
        delete tree;
}

void Forest::loadTrainingSample(const string training_file)
{
    printf("Loading training data from %s\n", training_file.c_str());
    ifstream fin(training_file);

    this->n_samples = 0;
    int class_id = -1;
    string line;
    while(getline(fin, line))
    {
        stringstream ss(line);
        Data data;
        for(int i = 0; i < this->n_features; i++)
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
        training_sample.push_back(data);
        n_samples++;
    }

    cout << "total data: " << training_sample.size();
    cout << " attribute: " << n_features;
    cout << " classes: " << class_name.size() << endl;
    fin.close();

    chooseValidationData(floor(n_samples*p_validations));
    return;
}

void Forest::chooseValidationData(unsigned int size)
{
    vector<bool> has_choose(n_samples, false);
    validation_data.clear();
    for(int i = 0; i < size; i++)
    {
        int rand_index = rand() % training_sample.size();
        while(has_choose[rand_index])
            rand_index = rand() % training_sample.size();

        has_choose[rand_index] = true;
        validation_data.push_back(training_sample[rand_index]);
    }

    for(int i = 0; i < n_samples; i++)
    {
        if(has_choose[i]) continue;
        training_data.push_back(training_sample[i]);
    }

    return;
}

void Forest::train()
{
    printf("-----forest training-----\n");
    int subset_size = training_data.size();

    for(int t= 0; t < n_trees; t++)
    {
        vector<Data> training_data_ = randomSubset(subset_size);
        printf("training tree[%d]\n", t);
        trees[t]->train(training_data_, class_name.size(), n_attribute_bagging, 0);
    }

    printf("-----finish training-----\n");
    printf("##########################################\n");
    printf(" training summary\n");
    printf(" trained %d cart\n", n_trees);
    printf(" classes: %lu\n", class_name.size());
    printf(" each data has %d attributes\n", n_features);
    printf(" training each tree with %d elements\n", subset_size);
    printf(" training each node using %d attributes\n", n_attribute_bagging);
    printf("##########################################\n\n");
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
