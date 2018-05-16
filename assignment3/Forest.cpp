#include "Forest.hpp"
using namespace std;

Forest::Forest() {}

Forest::Forest(int n_trees, int n_features)
{
    this->n_trees = n_trees;
    this->n_features = n_features;
}

Forest::~Forest() {}

void Forest::loadTrainingData(const char *training_file, int num_of_features)
{
    printf("Loading training data from %s\n", training_file);
    ifstream fin(training_file);
    this->n_features = num_of_features;

    int label_id = -1;
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

        string label_str;
        ss >> label_str;

        if(findLabel(label_str, classes) == -1)
        {
            classes.push_back(label_str);
            label_id++;
        }

        data.label.id = label_id;
        data.label.str = label_str;
        training_data.push_back(data);
    }

    for(int i = 0; i < n_trees; i++)
        trees.push_back(TreeNode(n_features));

    printf("total data: %d, attr: %d, classes: %d\n", training_data.size(), n_features, classes.size());
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
        trees[t].train(training_sample, classes.size(), 0);
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
    vector<int> class_vote(classes.size(), 0);
    for(auto tree : trees)
    {
        vector<double> distributions = tree.classify(data);
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

    printf("predict: %s, prob: %lf, ", classes[predict_class].c_str(), (double) max_vote / total_vote);
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

void sumUp(vector<double> dest, vector<double> src)
{
    assert(dest.size() == src.size());
    for(int i = 0; i < dest.size(); i++)
        dest[i] += src[i];

    return;
}

int findLabel(string label, vector<string> classes)
{
    for(int i = 0; i < classes.size(); i++)
    {
        if(classes[i] == label)
            return i;
    }

    return -1;
}
