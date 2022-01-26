#! /bin/bash

# Ten skrypt umożliwia uruchomienie testowego programu klienckiego
# W przypadku braku argumentów lub tylko z jednym argumentem zastąpi on brakujące domyslnym wartościami:
# IP = 127.0.0.1
# PORT = 6941

client_test_program/build/client_test_program $1 $2
