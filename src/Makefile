# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

# Note that binutils-2.20 doesn't handle mboot header well for some reason.
# I use this path for binutils 2.18 on systems that ship with the borken one.
PATH:=/opt/tc-vanilla/bin:$(PATH)

SOURCES += $(patsubst %.s, %.o, $(wildcard *.s))
SOURCES += $(patsubst %.c, %.o, $(wildcard *.c))
SOURCES += $(patsubst %.c, %.o, $(wildcard mm/*.c))
SOURCES += $(patsubst %.c, %.o, $(wildcard lib/*.c))
SOURCES += $(patsubst %.c, %.o, $(wildcard drivers/*.c))

CFLAGS =-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=gnu99 -g
CFLAGS+=-I. -I./lib -I./drivers -I./mm
LDFLAGS=-Tlink.ld
ASFLAGS=-felf
CC = $(CC_TARGET)
LD = $(LD_TARGET)

all: $(SOURCES) link

clean:
	find . -name '*.o' | xargs rm -f
	rm -f kernel

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
