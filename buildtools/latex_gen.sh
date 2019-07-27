#!/bin/bash

#latex has to be run several times (up to 3) to compile well (e.g. when there
#   is a multi-page table of contents)
runs_needed=3
runs_done=0

filepath=$1
cleanup_flag=$2
filedir=$(dirname "${filepath}")
filename=$(basename "${filepath}")

if [ "$filepath" == "" ]; then
    echo "no file specified"
    exit 1
fi

function rm_generated_files () {
    local filename_nosuf=$(basename "${filename}" .tex)
    rm -fv "$filename_nosuf.aux"
    rm -fv "$filename_nosuf.pyg"
    rm -fv "$filename_nosuf.out"
    rm -fv "$filename_nosuf.toc"
    rm -fv "$filename_nosuf.log"
}

function mv_generated_files () {
    local filename_nosuf=$(basename "${filename}" .tex)
    local aux_dirname="${filename_nosuf}_build_files"
    mkdir -p "${filename_nosuf}_build_files"
    mv -fv "$filename_nosuf.aux" \
       "$filename_nosuf.pyg" \
       "$filename_nosuf.out" \
       "$filename_nosuf.toc" \
       "$filename_nosuf.log" \
       "$aux_dirname"
    rm -rf "$aux_dirname/_minted-$filename_nosuf"
    mv -fv "_minted-$filename_nosuf" \
       "$aux_dirname/"
}

#some latex modules are capricious and want the latex compiler to be called
#   from the same directory where the source file is
cd $filedir

#remove auxilary latex files before we start, leftover *.aux has caused
#   compilation problems before
rm_generated_files

while [ $runs_done -lt $runs_needed ]; do
    echo
    echo "run #$(($runs_done +1))"
    echo

    #latex -shell-escape $filename
    pdflatex -shell-escape $filename
    if [ $? -ne 0 ]; then
        echo
        echo "there were latex compiler errors, aborting"
        exit 1
    fi
    runs_done=$((++runs_done))
done

if [ "$cleanup_flag" == "-m" ]; then
    mv_generated_files
fi

exit 0
