#!/bin/bash
# Usage ./_run.sh <testcase> [Optional Output filename]

DIRECTORY='outputs/'

if [ -z $1 ]; then
    echo "Usage $0 <testcase>"
    exit
fi

echo "Compiling ..."
g++ -g -o dijkstra dijkstra.cpp
# g++ -g -Wall -o dijkstra dijkstra.cpp

echo "Compiled"

if [ -z $2 ]; then
    ./dijkstra < $1
    exit
fi

./dijkstra < $1 > $2