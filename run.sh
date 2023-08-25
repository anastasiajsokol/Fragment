#!/bin/sh

set -e

g++ lexer/*.cpp main.cpp -o fragment

set +e

./fragment
result=$?
rm fragment
exit $result