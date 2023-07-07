#!/bin/bash

# Declare an array of numbers
numbers=(5 2 7 1 9)

# Length of the array
length=${#numbers[@]}

# Bubble sort algorithm
for ((i=0; i<$length-1; i++))
do
    for ((j=0; j<$length-i-1; j++))
    do
        if [[ ${numbers[j]} -gt ${numbers[j+1]} ]]
        then
            # Swap numbers[j] and numbers[j+1]
            temp=${numbers[j]}
            numbers[j]=${numbers[j+1]}
            numbers[j+1]=$temp
        fi
    done
done

# Print the sorted array
echo "Sorted numbers: ${numbers[@]}"
