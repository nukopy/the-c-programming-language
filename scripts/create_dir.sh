#!/bin/bash
# This script creates a directory with the name of the script
# MUST Execute on project root directory like "sh scripts/create_dir.sh"

CHAPTER_NUMBER_START=0
CHAPTER_NUMBER_END=8

for i in `seq $CHAPTER_NUMBER_START $CHAPTER_NUMBER_END`;
do
  DIRNAME="./src/$(printf "chap%02d" $i)"

  if [ -d $DIRNAME ]; then
    echo "Directory $DIRNAME already exists"
  else
    mkdir $DIRNAME
    echo "Directory $DIRNAME created"
  fi

done
