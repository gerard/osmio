# vim: set filetype=make :
UNAME=$(shell uname)
UNAME_ARCH=$(shell uname -m)
LD_IS_BLACKLISTED=$(shell ./scripts/is_ld_blacklisted.sh)
HAS_CLANG=$(shell which llvm-clang)

# Some newer ld versions seem to have changed behaviour respect to the
# multiboot header on 64 bits.  I don't see how to do it properly.  Until then
# you can define your own CC and LD here
LD_BLACKLIST=2.20.1-system.20100303

# Safe old default
CC_HOST=gcc
CC_TARGET=gcc
LD_TARGET=ld

ifeq ($(UNAME), Darwin)
	include build/defs.osx.inc
endif

ifeq ($(UNAME), Linux)

	# Generally nicer error output.  Use it while we don't find a reason not to.
    ifneq "" "$(HAS_CLANG)"
        $(warning Using clang...)
        include build/defs.llvm-clang.inc
    endif

    ifeq (yes,$(LD_IS_BLACKLISTED))
        $(warning Your binutils are blacklisted.  Using alternative...)
        include build/defs.custom-ld.inc
    endif

endif
