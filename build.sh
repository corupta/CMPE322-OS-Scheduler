#!/bin/bash

if ! [ -x "$(command -v cmake)" ]; then
  echo 'Error: cmake is not installed.'
  exit 1
fi

if ! [ -x "$(command -v make)" ]; then
  echo 'Error: make is not installed.'
  exit 1
fi

cmake CMakeLists.txt
make
echo "Successfully built cmpe322_project_1, deleting intermediary build files and caches"
rm -r CMakeFiles
rm cmake_install.cmake
rm CMakeCache.txt
rm cmpe322_project_1.cbp
rm Makefile
echo "Deleted intermediary files, "
