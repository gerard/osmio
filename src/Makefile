# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

# Note that binutils-2.20 doesn't handle mboot header well for some reason.
# I use this path for binutils 2.18 on systems that ship with the borken one.
PATH:=/opt/tc-vainilla/bin:$(PATH)
SOURCES=boot.o main.o printf.o common.o console.o

CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=gnu99 -I.
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	rm -f *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
