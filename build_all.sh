#! /bin/bash

for dir in socket server client message
do
   cd $dir
   ./build.sh
   if [ $? -gt 0 ]
   then
     echo "Error in script build $dir"
     exit 1
   fi
   cd ..
done
