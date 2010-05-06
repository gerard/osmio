# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

# Note that binutils-2.20 doesn't handle mboot header well for some reason.
# I use this path for binutils 2.18 on systems that ship with the borken one.
PATH:=/opt/tc-vanilla/bin:$(PATH)

SOURCES += $(patsubst %.s, %.o, $(wildcard *.s))
SOURCES += $(patsubst %.c, %.o, $(wildcard *.c))

CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=gnu99 -I. -g
LDFLAGS=-Tlink.ld
ASFLAGS=-felf
CC=PATH=$(PATH) gcc
LD=PATH=$(PATH) ld

all: $(SOURCES) link

clean:
	rm -f *.o kernel

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
