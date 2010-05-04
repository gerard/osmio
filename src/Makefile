# Makefile for JamesM's kernel tutorials.
# The C and C++ rules are already setup by default.
# The only one that needs changing is the assembler 
# rule, as we use nasm instead of GNU as.

# binutils-2.20 doesn't handle mboot header well for some reason
LD=/opt/tc-vanilla/bin/ld
SOURCES=boot.o main.o sprintf.o common.o

CFLAGS=-m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -std=gnu99 -I.
LDFLAGS=-Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	rm -f *.o kernel

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
