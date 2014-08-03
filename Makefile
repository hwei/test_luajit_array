
LUAINC=-I$(HOME)/git/luajit-2.0/src

CC=gcc
CFLAGS= $(LUAINC) -pedantic -Wall -O2 -fno-common -m32
LDFLAGS=-bundle -undefined dynamic_lookup -Wl,-all_load -m32
LD=export MACOSX_DEPLOYMENT_TARGET="10.3"; gcc

RAWARRAY_O=rawarray.o

RAWARRAY_BUNDLE=rawarray.bundle

all: $(RAWARRAY_BUNDLE)

clean:
	rm *.bundle *.o

$(RAWARRAY_BUNDLE): $(RAWARRAY_O)
	$(LD) $(LDFLAGS) $+ -o $@

rawarray.o: rawarray.c
