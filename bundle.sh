#!/bin/bash

if ! [ -x "$(command -v markdown-pdf)" ]; then
  echo 'Error: markdown-pdf is not installed.'
  echo 'Please install it with npm i -g markdown-pdf';
  echo 'If npm fails, try again using node version 8';
  exit 1
fi

if ! [ -x "$(command -v ots)" ]; then
  echo 'Error: ots (opentimestamps-client) is not installed.'
  exit 1
fi

if ! [ -x "$(command -v zip)" ]; then
  echo 'Error: zip is not installed.'
  exit 1
fi

./test.sh
./run.sh

rm 2016400141.zip
rm 2016400141.zip.ots
cd Report_Documentation
markdown-pdf Report.md -o Report.pdf
markdown-pdf Documentation.md -o Documentation.pdf
mv Report.pdf ../Report.pdf
mv Documentation.pdf ../Documentation.pdf
cd ..

zip 2016400141.zip -r src "Provided Files" build.sh run.sh test.sh CMakeLists.txt cmpe322_project_1 custom_output.txt main.cpp README.md Report.pdf Documentation.pdf
ots stamp 2016400141.zip
# ots upgrade 2016400141.zip.ots
rm Report.pdf
rm Documentation.pdf
rm -r 2016400141
unzip 2016400141.zip -d 2016400141

echo "Zip 2016400141.zip is created, don't forget to check its contents"
echo "Also, don't forget to push the .zip and .ots to github"
echo "Also don't forget to send the .zip to moodle"
echo "And, press the extra final submit button on moodle";
