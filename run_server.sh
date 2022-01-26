#! /bin/bash
# Ten skrypt umożliwia uruchomienie serwera z domyślnymi parametrami
ls | grep .test_file | xargs rm -f
server/build/server $1 $2
ls | grep .test_file | xargs rm -f
