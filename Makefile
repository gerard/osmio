include build/system.inc

export CC_TARGET	?= gcc
export LD_TARGET	?= ld
export CC_HOST		?= gcc

MEM	?= 32
ISO	?= osmio.iso

CTIME=$(shell date +%y%m%d-%H.%M.%S)

all: test run-qemu

src/kernel:
	make -C src

osmio.iso: src/kernel
	./scripts/gen-osmio-iso.sh $(ISO)

run-qemu: osmio.iso
	[ -n "$$DISPLAY" ] && qemu -cdrom $(ISO) -m $(MEM)

run-bochs: osmio.iso
	[ -n "$$DISPLAY" ] && bochs -f bochs/config 'log: logs/bochs-$(CTIME)' \
												'megs: $(MEM)'

test:
	make -C t

clean:
	make -C src clean
	make -C t clean
	rm -f $(ISO) bochslog.txt

logs-clean:
	rm -f logs/*
