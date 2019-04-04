#!/bin/bash

#latex has to be run several times (up to 3) to compile well (e.g. when there is a multi-page table of contents)
runs_needed=3
runs_done=0

filename=$1

if [ "$filename" == "" ]; then
    echo "no file specified"
    exit 1
fi

while [ $runs_done -lt $runs_needed ]; do
    echo
    echo "run #$(($runs_done +1))"
    echo

    latex $filename
    if [ $? -ne 0 ]; then
        echo
        echo "there were latex compiler errors, aborting"
        exit 1
    fi
    runs_done=$((++runs_done))
done
