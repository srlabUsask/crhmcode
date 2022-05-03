#!/bin/bash

mkdir build
cd ./build
cmake ../ -DSTAGING_DIR=.
make install
