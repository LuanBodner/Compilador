#!/bin/bash

#Build Project
make all

#Execute Project
./compiler tiny.txt token.txt tree.txt

#Generate .ll file
llvm-dis tiny.bc
