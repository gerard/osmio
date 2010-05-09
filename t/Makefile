CFLAGS=-g -I./stubs -I../src/lib -std=gnu99
LDFLAGS=-lcheck

# FIXME: Get some proper makefiles (ones in bugnes?)

all: bitset-run

bitset.o: ../src/lib/bitset.c
	$(CC) $^ -c -o $@ $(CFLAGS)

bitset-test: bitset.o bitset-test.o
	$(CC) $^ -o $@ $(LDFLAGS)

bitset-run: bitset-test
	for exe in $^; do ./$$exe; done

clean:
	rm -f bitset-test *.o
