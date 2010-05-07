#!/bin/sh
set -e

cd src
make clean
make
cd -

cd t
make clean
make

for i in *-test
do
    ./$i
done

cd -
./update_image.sh
./run_qemu.sh
