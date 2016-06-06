#!/bin/bash

###### Main

WARG=0

if [ "$#" == 0 ]
then
    echo "Wrong number of Arguments"
    echo "OPT : clean || build || all || execute"
else
    
    if [ "$1" == "clean" ] || [  "$1" == "all" ];
    then
        make clean
        WARG=1
    fi

    if [ "$1" == "build" ] || [ "$1" == "all" ];
    then
        make all
        WARG=1
    fi

    if [ "$1" == "execute" ] || [ "$1" == "all" ];
    then
        ./compiler tiny.txt token.txt tree.txt
        llvm-dis tiny.bc
        WARG=1
    fi

    if [ $WARG == 0 ];
    then
        echo "Wrong Argument"
    fi
fi