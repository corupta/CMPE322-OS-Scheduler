#!/bin/bash

rm cmpe322_project_1
./build.sh
cd "Provided Files"
../cmpe322_project_1 ../custom_output.txt
echo "Successfully run and created custom_output.txt"