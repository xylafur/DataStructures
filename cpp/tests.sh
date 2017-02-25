#!/bin/sh

g++ -Wall -pedantic -std=c++11 -o runner runner.cpp
echo "Running tests: "
./runner
rm -rf ./runner
