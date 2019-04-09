#!/bin/bash

#latex has to be run several times (up to 3) to compile well (e.g. when there is a multi-page table of contents)
runs_needed=3
runs_done=0

filepath=$1

if [ "$filepath" == "" ]; then
    echo "no file specified"
    exit 1
fi

filedir=$(dirname "${filepath}")
filename=$(basename "${filepath}")

#some latex modules are capricious and want the latex compiler to be called from the same directory where the source file is
cd $filedir

#remove auxilary latex files before we start, *.aux has caused compilation problems before
rm -f *.aux
rm -f *.pyg
rm -f *.out
rm -f *.toc

while [ $runs_done -lt $runs_needed ]; do
    echo
    echo "run #$(($runs_done +1))"
    echo

    latex -shell-escape $filename
    if [ $? -ne 0 ]; then
        echo
        echo "there were latex compiler errors, aborting"
        exit 1
    fi
    runs_done=$((++runs_done))
done

exit 0
