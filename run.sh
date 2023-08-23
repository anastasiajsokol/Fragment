#!/bin/sh

set -e

g++ main.cpp -o fragment

set +e

./fragment
result=$?
rm fragment
exit $result