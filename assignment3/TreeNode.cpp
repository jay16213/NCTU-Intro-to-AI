#include "TreeNode.hpp"
using namespace std;

#define MIN_IMPURITY 0.01

TreeNode::TreeNode()
{
    left_child = NULL;
    right_child = NULL;
    threshold.id = -1;
    threshold.value = 0.0;
    this->num_of_attributes = 0;
}

TreeNode::TreeNode(int num_of_attributes)
{
    left_child = NULL;
    right_child = NULL;
    threshold.id = -1;
    threshold.value = 0.0;
    this->num_of_attributes = num_of_attributes;
}

TreeNode::~TreeNode()
{
    if(left_child != NULL)
        delete left_child;
    if(right_child != NULL)
        delete right_child;
}

void TreeNode::split(const vector<Data> &src, Attribute threshold, vector<Data> &less, vector<Data> &greater)
{
    less.clear();
    greater.clear();

    for(auto data : src)
    {
        assert(threshold.id >= 0);
        assert(threshold.id < data.attributes.size());
        if(data.attributes[threshold.id].value <= threshold.value)
            less.push_back(data);
        else
            greater.push_back(data);
    }

    return;
}

vector<double> TreeNode::extractAttribute(const vector<Data> &data, int attribute_id)
{
    vector<double> result;

    for(auto d : data)
        result.push_back(d.attributes[attribute_id].value);

    return result;
}

vector<double> TreeNode::computeThresholdValues(vector<double> &attribute)
{
    vector<double> thresh;
    sort(attribute.begin(), attribute.end());

    for(int i = 0; i < attribute.size() - 1; i++)
    {
        double t = (attribute[i] + attribute[i+1]) / 2.0;
        thresh.push_back(t);
    }

    return thresh;
}

vector<int> TreeNode::attributeBagging(int n_attribute_bagging)
{
    vector<int> result(num_of_attributes);
    for(int i = 0; i < num_of_attributes; i++)
        result[i] = i;

    random_shuffle(result.begin(), result.end());
    result.resize(n_attribute_bagging);
    return result;
}

void TreeNode::train(vector<Data> data, int n_classes, int n_attribute_bagging, int dep)
{
    assert(data.size() > 0);

    if(data.size() <= 1 || dep >= 10)
    {
        distribution = computePValue(data, n_classes);
        return;
    }

    double min_impurity = 1000000000.0;
    Attribute best_thresh;

    // TODO: attribute bagging
    vector<int> bagged_attribute = attributeBagging(n_attribute_bagging);

    vector<double> attribute(data.size(), 0.0), threshold_values(data.size(), 0.0);
    vector<Data> less(data.size()), greater(data.size());
    for(auto attribute_id : bagged_attribute)
    {
        attribute = extractAttribute(data, attribute_id);
        threshold_values = computeThresholdValues(attribute);
        assert(threshold_values.size() > 0);

        Attribute thresh;
        thresh.id = attribute_id;
        for(auto threshold_value : threshold_values)
        {
            thresh.value = threshold_value;
            this->split(data, thresh, less, greater);
            double impurity = totalImpurity(less, greater, n_classes);

            if(impurity < min_impurity)
            {
                min_impurity = impurity;
                best_thresh.id = attribute_id;
                best_thresh.value = threshold_value;
            }
        }
    }

    if(min_impurity <= MIN_IMPURITY)
    {
        distribution = computePValue(data, n_classes);
        return;
    }

    this->split(data, best_thresh, less, greater);
    if(less.empty() || greater.empty())
    {
        distribution = computePValue(data, n_classes);
        return;
    }

    // save best threshold
    this->threshold = best_thresh;
    printf("[%d] select threshold %lf\n", dep, threshold.value);

    // printf("less: %lu, greater: %lu\n", less.size(), greater.size());
    left_child = new TreeNode(num_of_attributes);
    left_child->train(less, n_classes, n_attribute_bagging, dep + 1);

    right_child = new TreeNode(num_of_attributes);
    right_child->train(greater, n_classes, n_attribute_bagging, dep + 1);

    return;
}

vector<double> TreeNode::classify(Data data)
{
    if(threshold.id == -1)
        return distribution;

    assert(threshold.id >= 0);
    assert(threshold.id < data.attributes.size());

    if(data.attributes[threshold.id].value <= threshold.value)
    {
        assert(left_child != NULL);
        return left_child->classify(data);
    }
    else
    {
        assert(right_child != NULL);
        return right_child->classify(data);
    }
}

vector<double> computePValue(const vector<Data> &classes, int num_of_classes)
{
    if(classes.size() == 1)
    {
        vector<double> p_values(num_of_classes, 0);
        p_values[classes[0].class_id] = 1.0;
        return p_values;
    }

    assert(classes.size() > 0);

    vector<int> count(num_of_classes, 0);
    for(auto c : classes)
    {
        assert(c.class_id >= 0);
        assert(c.class_id < num_of_classes);
        count[c.class_id]++;
    }

    vector<double> p_values;
    for(auto cnt : count)
    {
        double p = ((double) cnt) / classes.size();
        p_values.push_back(p);
    }

    return p_values;
}

inline double giniImpurity(const vector<Data> &classes, int num_of_classes)
{
    if(classes.size() == 0) return 0.0;

    vector<double> p_values = computePValue(classes, num_of_classes);

    double result = 1.0;
    for(auto p : p_values)
        result -= p*p;

    return result;
}

inline double totalImpurity(const vector<Data> &less, const vector<Data> &greater, int num_of_classes)
{
    double gini_less = giniImpurity(less, num_of_classes);
    double gini_greater = giniImpurity(greater, num_of_classes);

    int total = less.size() + greater.size();
    double total_impurity = ((double)less.size() / total)*gini_less + ((double)greater.size() / total)*gini_greater;
    return total_impurity;
}
