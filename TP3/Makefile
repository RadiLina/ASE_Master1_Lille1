
ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -m32 -Wall -ansi -std=gnu99 -pedantic 
CFLAGS  += -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

###------------------------------
### Main rules 
###------------------------------------------------------------
all: ordonnanceur create_ctx
create_ctx: create_ctx.o
	$(CC) $(CFLAGS) -o create_ctx  create_ctx.o         
create_ctx.o: create_ctx.c
	$(CC) $(CFLAGS)  -c create_ctx.c 

ordonnanceur :ordonnanceur.o
	$(CC) $(CFLAGS) -o ordonnanceur ordonnanceur.o $(LIBS) 
ordonnanceur.o :ordonnanceur.c hwconfig.h 
	$(CC) $(CFLAGS) $(INCS) -c ordonnanceur.c 

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o 
realclean: clean 
	$(RM) ordonnanceur create_ctx
