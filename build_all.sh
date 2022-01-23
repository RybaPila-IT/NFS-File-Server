#! /bin/bash

for dir in socket message server client client_test_program
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
