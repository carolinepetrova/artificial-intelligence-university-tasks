#!/usr/bin/bash

g++ -std=c++17 -ggdb test.cpp -o test && ./test

if [[ $? -ne 0 ]]; then
    echo "Unit tests failed! Will not run program!";
    exit 1
fi

g++ -std=c++17 -ggdb main.cpp -o main && ./main > results.txt

