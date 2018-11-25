#!/bin/bash

if ! [ -x "$(command -v diff)" ]; then
  echo 'Error: diff is not installed.'
  exit 1
fi

# remove old built binary
rm cmpe322_project_1
rm test_output.txt

./build.sh

cd "Provided Files"
mv output.txt original_output.txt
../cmpe322_project_1
DIFF=$(diff output.txt original_output.txt)
mv output.txt ../test_output.txt
mv original_output.txt output.txt
cd ..
if [ -z "$DIFF" ]; then
    echo "New Output is identical to the provided one. Test is successful!"
    echo "Deleting test_output.txt"
    rm test_output.txt;
else
    echo "Differences:"
    echo "${DIFF}"
    echo "New Output is different than the provided one. Test failed!"
    echo "Won't delete test_output.txt so the differences can be checked"
fi
