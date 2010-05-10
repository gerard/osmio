#!/bin/sh

LD_BLACKLIST="2.20.1-system.20100303"
LD_VERSION=`ld -v | sed 's/.*)\ //'`

for ITEM in $LD_BLACKLIST
do
    [ "$LD_VERSION" = "$ITEM" ] && echo "yes" && exit 0
done

echo no
