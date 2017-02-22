#!/bin/sh

g++ -Wall -pedantic -o runner runner.cpp
echo "Running tests: "
./runner
