#!/bin/bash

cross200_tree="cross200_tree.csv"
iris_tree="iris_tree.csv"
rm $cross200_tree
rm $iris_tree

# test number of trees
for ntree in $(seq 1 50)
do
    rate="$(./random_forest -t cross200.txt -f 2 -a 2 -n $ntree | grep get)"
    echo $rate | awk '{print $2","$3}' >> $cross200_tree
    echo "${ntree} ${rate}"
done

for ntree in $(seq 1 50)
do
    rate="$(./random_forest -t iris.txt -f 4 -a 4 -n $ntree | grep get)"
    echo $rate | awk '{print $2","$3}' >> $iris_tree
    echo "${ntree} ${rate}"
done
