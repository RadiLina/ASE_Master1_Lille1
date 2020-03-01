ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -m32 -Wall -ansi -std=gnu99 -pedantic 
CFLAGS  += -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

###------------------------------
### Main rules 
###------------------------------------------------------------
all: prodcons sem
prodcons: prodcons.o sem.o
	$(CC) $(CFLAGS) -o prodcons  prodcons.o  sem.o       
prodcons.o: prodcons.c 
	$(CC) $(CFLAGS)  -c prodcons.c 

sem :sem.o
	$(CC) $(CFLAGS) -o sem sem.o $(LIBS) 
sem.o :sem.c hwconfig.h 
	$(CC) $(CFLAGS) $(INCS) -c sem.c 

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o 
realclean: clean 
	$(RM) prodcons sem

