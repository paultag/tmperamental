include ../version.mk

LIB=../lib/
INC=../include/

TARGETS=$(shell ls *.c | sed s/.c$$/.o/g)
CFLAGS=-Wall -c -fPIC -I$(INC)  # FIXME
CC=gcc  # FIXME

LDFLAGS=-shared \
		-Wl,--no-as-needed \
		-ldl \
		-Wl,-soname,$(LIB_NAME).so.$(LIB_MAJOR).$(LIB_MINOR)

OUTPUT=$(LIB)$(LIB_NAME).so.$(LIB_MAJOR).$(LIB_MINOR)

build: $(TARGETS) link

clean:
	rm -f *.o
	rm -f $(OUTPUT)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

link:
	$(CC) $(LDFLAGS) $(TARGETS) -o $(OUTPUT)
