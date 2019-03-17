#!/bin/bash
# Usage ./run.sh for redirecting outputs to file,
# and with an argument to print on commandline as well

DIRECTORY='outputs/'

if [ -d "$DIRECTORY" ]; then
    rm -rf "$DIRECTORY"
fi
mkdir "$DIRECTORY"

g++ -g -Wall -o dijkstra dijkstra.cpp

for testcase in $(ls testcases); do
    OUTPUT="$DIRECTORY$testcase.temp"

    ./dijkstra < testcases/$testcase > $OUTPUT
    if [ $1 ]; then
        printf "===============================================\n\n\n"
        printf "Reading input $testcase ↓\n"
        cat $OUTPUT
    fi

    printf "$testcase ✔ \n"
done