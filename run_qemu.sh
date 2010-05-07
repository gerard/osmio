#!/bin/sh

# Don't run if we don't have a X server running
if [ -n "$DISPLAY" ]
then
    qemu -fda floppy.img -m 32
else
    # TODO: When the kernel gets support for it, we can run it without X over
    # the serial port.  Right now, just don't...
    #qemu -fda floppy.img -m 32 -nographic
    true
fi
