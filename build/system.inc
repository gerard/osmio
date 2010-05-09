UNAME=$(shell uname)

ifeq ($(UNAME), Darwin)
	include build/defs.osx.inc
endif
