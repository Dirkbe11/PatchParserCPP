#clean up existing build directory
rm -r build

#set up new build directory for cmake artifacts
mkdir build
cd build

#build the test and execute
cmake ..
make
./PatchParseTest

#remove the leftover artifacts
cd ..
rm -r build
