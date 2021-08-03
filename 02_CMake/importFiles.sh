#!/bin/bash

cp ../01_Matlab/codegen/lib/model31_func/*.cpp src/
cp ../01_Matlab/codegen/lib/model31_func/*.h src/
# cp ../01_Matlab/*.txt unitTestFiles/
ln const_src/main.cpp src/main.cpp
ln const_src/main.h src/main.h
ln const_src/tmwtypes.h src/tmwtypes.h
ln const_src/unitTest.h src/unitTest.h
ln const_src/CMakeLists.txt src/CMakeLists.txt

# echo "update files list in CMakeLists.txt to:"
# find . -maxdepth 1 -name "*.c" -o -name "*.h" | cut -d/ -f2 | sort | grep -v main
# echo main.c

