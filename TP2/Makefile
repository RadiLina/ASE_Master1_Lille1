CFLAGS= -O0 -g -m32 -Wall -fno-pic
LDFLAGS= -m32

all: switch_to

switch_to: switch_to.o
switch_to.o: switch_to.c

switchTo:switch_to
	./switch_to

clean: 
	rm -f *.o switch_to

.PHONY: clean

