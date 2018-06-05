#!/bin/bash
SCP_DIR=$(cd $(dirname $0);pwd);
cd $SCP_DIR/../docs/
sudo rm -rf ./*

cd $SCP_DIR/../src/
doxygen
cd ../docs/html
sudo mv ./* ../
