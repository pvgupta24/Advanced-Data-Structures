#!/bin/bash
# Usage ./runtests.sh for redirecting outputs to file,
# and with an arguement to print on commandline as well

DIRECTORY='outputs/'

if [ -d "$DIRECTORY" ]; then
    rm -rf "$DIRECTORY"
fi
mkdir "$DIRECTORY"

g++ -g -Wall -o rbt rbt_merge.cpp RedBlackTree.cpp -o rbt

for testcase in $(ls testcases); do
    TEMP_OUTPUT="$DIRECTORY$testcase.temp"

    ./rbt < testcases/$testcase > $TEMP_OUTPUT
    if [ $1 ]; then
        printf "===============================================\n\n\n"
        printf "Reading input $testcase ↓\n"
        cat $TEMP_OUTPUT
    fi

    FILTERED_OUTPUT='sed -r "s/\x1B\[([0-9]{1,2}(;[0-9]{1,2})?)?[m|K]//g" $TEMP_OUTPUT'
    FINAL_OUTPUT="${TEMP_OUTPUT%.*}"
    eval $FILTERED_OUTPUT > $FINAL_OUTPUT
    rm $TEMP_OUTPUT

    printf "$testcase scanned. ✔ \n"
done