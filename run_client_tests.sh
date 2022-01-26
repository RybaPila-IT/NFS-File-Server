#! /bin/bash
# Ten skrypt umożliwia uruchomienie programu testowego klienta z domyślnymi parametrami
ls | grep .test_file | xargs rm -f
client_test_program/build/client_test_program $1 $2
ls | grep .test_file | xargs rm -f
