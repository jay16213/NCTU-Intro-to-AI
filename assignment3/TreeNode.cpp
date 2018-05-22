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

vector<double> TreeNode::computeThresholdValues(vector<double> attribute)
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

void TreeNode::train(const vector<Data> &data, int n_classes, int n_attribute_bagging, int dep)
{
    assert(data.size() > 0);
    vector<int> classes = extractClasses(data);

    if(data.size() == 1)
    {
        distribution = computePValue(classes, n_classes);
        return;
    }


    Attribute best_thresh;
    vector<int> bagged_attribute = attributeBagging(n_attribute_bagging);
    vector<double> attribute(data.size(), 0.0), threshold_values(data.size(), 0.0);

    double min_impurity = 1000000000.0;

    for(auto attribute_id : bagged_attribute)
    {
        attribute = extractAttribute(data, attribute_id);
        threshold_values = computeThresholdValues(attribute);
        assert(threshold_values.size() > 0);

        Attribute thresh;
        thresh.id = attribute_id;
        vector<int> _less, _greater;
        _less.reserve(data.size());
        _greater.reserve(data.size());
        for(auto threshold_value : threshold_values)
        {
            thresh.value = threshold_value;
            splitClass(classes, attribute, threshold_value, _less, _greater);
            double impurity = totalImpurity(_less, _greater, n_classes);

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
        distribution = computePValue(classes, n_classes);
        return;
    }

    vector<Data> less, greater;
    less.reserve(data.size());
    greater.reserve(data.size());

    this->split(data, best_thresh, less, greater);

    if(less.empty() || greater.empty())
    {
        distribution = computePValue(classes, n_classes);
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

void splitClass(
    const vector<int> &classes,
    const vector<double> &attribute,
    double threshold,
    vector<int> &less,
    vector<int> &greater
    )
{
    assert(classes.size() == attribute.size());

    less.clear();
    greater.clear();

    for(int i = 0; i < classes.size(); i++)
    {
        if(attribute[i] <= threshold)
            less.push_back(classes[i]);
        else
            greater.push_back(classes[i]);
    }

    return;
}

inline vector<int> extractClasses(const vector<Data> &data)
{
    vector<int> classes;
    classes.reserve(data.size());
    for(auto d : data)
        classes.push_back(d.class_id);

    return classes;
}

vector<double> computePValue(const vector<int> &classes, int num_of_classes)
{
    if(classes.size() == 1)
    {
        vector<double> p_values(num_of_classes, 0);
        p_values[classes[0]] = 1.0;
        return p_values;
    }

    assert(classes.size() > 0);

    vector<int> count(num_of_classes, 0);
    for(auto c : classes)
    {
        assert(c >= 0);
        assert(c < num_of_classes);
        count[c]++;
    }

    vector<double> p_values;
    for(auto cnt : count)
    {
        double p = ((double) cnt) / classes.size();
        p_values.push_back(p);
    }

    return p_values;
}

inline double giniImpurity(const vector<int> &classes, int num_of_classes)
{
    if(classes.size() == 0) return 0.0;

    vector<double> p_values = computePValue(classes, num_of_classes);

    double result = 1.0;
    for(auto p : p_values)
        result -= p*p;

    return result;
}

inline double totalImpurity(const vector<int> &less, const vector<int> &greater, int num_of_classes)
{
    double gini_less = giniImpurity(less, num_of_classes);
    double gini_greater = giniImpurity(greater, num_of_classes);

    int total = less.size() + greater.size();
    double total_impurity = ((double)less.size() / total)*gini_less + ((double)greater.size() / total)*gini_greater;
    return total_impurity;
}
