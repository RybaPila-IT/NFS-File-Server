#! /bin/bash

ROOT_DIR=pwd

for dir in socket server client
do
   cd $PWD/$dir
  ./build.sh
done
