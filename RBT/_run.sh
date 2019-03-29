#!/bin/bash
# Usage ./_run.sh <testcase>

DIRECTORY='outputs/'

if [ -z $1 ]; then
    echo "Usage $0 <testcase>"
    exit
fi

echo "Compiling ..."
g++ -g -Wall -o rbt rbt_merge.cpp RedBlackTree.cpp -o rbt

if [ -z $2 ]; then
    ./rbt < $1
    exit
fi

./rbt < $1 > $2