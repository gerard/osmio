#!/bin/sh

set -e
TMPDIR=`mktemp -d osmio-build.XXXXXX`
MKISOFS_OPTS='-input-charset utf-8 -R -no-emul-boot -boot-load-size 4 -boot-info-table'
[ -z "$KERNEL_FILE" ] && KERNEL_FILE=src/kernel
[ -n "$1" ] && ISO_FILE="$1"
[ -z "$ISO_FILE" ] && ISO_FILE=osmio.iso
MENU_LST_FILE=grub/menu.lst


mkdir -p $TMPDIR/boot/grub

[   -z "$GRUB_STAGE2" ] && GRUB_STAGE2=/usr/lib/grub/i386-pc/stage2_eltorito
[ ! -f "$GRUB_STAGE2" ] && GRUB_STAGE2=grub/stage2_eltorito
[ ! -f "$GRUB_STAGE2" ] && wget http://dropbox.geeksynapse.net/stage2_eltorito -P grub/

cp $GRUB_STAGE2 $TMPDIR/boot/grub
cp $KERNEL_FILE $TMPDIR
cp $MENU_LST_FILE $TMPDIR/boot/grub

cd $TMPDIR
find .
cd - > /dev/null

mkisofs -b boot/grub/stage2_eltorito $MKISOFS_OPTS -o $ISO_FILE $TMPDIR
rm -rf $TMPDIR
