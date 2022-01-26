#! /bin/bash

# Ten skrypt umożliwia uruchomienie serwera
# W przypadku braku argumentów lub tylko z jednym argumentem zastąpi on brakujące domyslnym wartościami:
# IP = 127.0.0.1
# PORT = 6941

if [ ! -d "build" ]; then
    mkdir tmp
fi
cd tmp
ls | grep .test_file | xargs rm -f
../server/build/server $1 $2
ls | grep .test_file | xargs rm -f
cd ..
