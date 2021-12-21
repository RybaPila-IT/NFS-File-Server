#! /bin/bash

ROOT_DIR=pwd

cd socket
.build.sh
cd $ROOT_DIR/server
./build.sh
cd $ROOT_DIR/client
./build.sh
