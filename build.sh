#!/bin/bash
#this should allow recompilation of the source code
if [ ! -d "build/" ]; then
    mkdir build
fi

cd build
cmake ..
make

cd ..
# comment this out when working with tortuga
if ! grep -q source\ $(pwd)/devel/setup.bash  ~/.bashrc; then
    echo "source $(pwd)/devel/setup.bash" >> ~/.bashrc
fi
