#! /bin/bash

for dir in socket message server client
do
   cd $dir
   rm -fr build
   ./build.sh
   if [ $? -gt 0 ]
   then
     echo "Error in script build $dir"
     exit 1
   fi
   cd ..
done
