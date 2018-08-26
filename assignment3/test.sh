#!/bin/bash

cross200_tree="cross200_tree.csv"
iris_tree="iris_tree.csv"
# optical_digits="optical-digits_tree.csv"
# rm $cross200_tree
# rm $iris_tree
# rm $optical_digits

# test number of trees
# for ntree in $(seq 1 50)
# do
#     rate="$(./random_forest -t cross200.txt -f 2 -a 2 -n $ntree | grep training:)"
#     echo $rate | awk '{print $2,$4}' >> $cross200_tree
#     echo "${ntree} ${rate}"
# done

# rm $iris_tree
# for ntree in $(seq 1 50)
# do
#     rate="$(./random_forest -t iris2.txt -f 4 -a 4 -n $ntree | grep training:)"
#     echo $rate | awk '{print $2,$4}' >> $iris_tree
#     echo "${ntree} ${rate}"
# done

# for ntree in $(seq 1 30)
# do
#     rate="$(./random_forest -t optical-digits.txt -f 64 -a 2 -n $ntree | grep training:)"
#     echo $rate | awk '{print $2,$4}' >> $optical_digits
#     echo "${ntree} ${rate}"
# done

# optical_digits_valid="optical-digits_valid.csv"
# for pv in $(seq 1 99)
# do
#     pv2=$(echo "${pv}*0.01" |bc)
#     rate="$(./random_forest -t optical-digits.txt -f 64 -a 2 -n 8 -s $pv2 | grep training:)"
#     echo $rate | awk '{print $2,$4}' >> $optical_digits_valid
#     echo "${pv2} ${rate}"
# done

# cross_valid="cross200_valid.csv"
# for pv in $(seq 1 99)
# do
#     pv2=$(echo "${pv}*0.01" |bc)
#     rate="$(./random_forest -t cross200.txt -f 2 -a 2 -n 8 -s $pv2 | grep training:)"
#     echo $rate | awk '{print $2,$4}' >> $cross_valid
#     echo "${pv2} ${rate}"
# done

iris_valid="iris_valid.csv"
rm $iris_valid
for pv in $(seq 1 99)
do
    pv2=$(echo "${pv}*0.01" |bc)
    rate="$(./random_forest -t iris.txt -f 4 -a 4 -n 16 -s $pv2 | grep training:)"
    echo $rate | awk '{print $2,$4}' >> $iris_valid
    echo "${pv2} ${rate}"
done

# optical_digits_bag="optical-digits_bag.csv"
# for attr in $(seq 1 64)
# do
#     echo "./random_forest -t optical-digits.txt -f 64 -a $attr -n 4 | grep training:"
#     rate="$(./random_forest -t optical-digits.txt -f 64 -a $attr -n 4 | grep training:)"
#     echo $rate | awk '{print $2,$4}' >> $optical_digits_bag
#     echo "${attr} ${rate}"
# done

# iris_bag="iris_bag.csv"
# rm $iris_bag
# for attr in $(seq 1 4)
# do
#     rate="$(./random_forest -t iris.txt -f 4 -a $attr -n 16 | grep training:)"
#     echo $rate | awk '{print $2,$4}' >> $iris_bag
#     echo "${attr} ${rate}"
# done
