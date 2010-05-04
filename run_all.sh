#!/bin/sh
set -e

cd src
make clean
make
cd -
./update_image.sh
./run_bochs.sh
