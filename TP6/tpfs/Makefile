# $Id: Makefile,v 1.1 2002/12/06 14:25:18 marquet Exp $
##############################################################################

ROOTDIR=/home/enseign/ASE

CC	= gcc
CFLAGS	= -Wall -ansi -pedantic
CFLAGS  += -g -m32
LIBDIR  = -L$(ROOTDIR)/lib
INCDIR  = -I$(ROOTDIR)/include
LIBS    =-L$(LIBDIR) -lhardware

###------------------------------
### Main targets
###------------------------------------------------------------
BINARIES= mkhd dmps frmt mkvol dvol
OBJECTS	= $(addsuffix .o,\
	  drive mbr)

all: $(BINARIES) $(OBJECTS)

###------------------------------
### Binaries
###------------------------------------------------------------
mkhd: mkhd.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)
dmps: dmps.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)
frmt: frmt.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)
mkvol: mkvol.o mbr.o drive.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)
dvol: dvol.o mbr.o drive.o
		$(CC) $(CFLAGS) -o $@ $^ $(LIBDIR) $(LIBS)

###------------------------------
### #include dependences
###------------------------------------------------------------
# you may fill these lines with "make depend"
mkhd.o: mkhd.c
dmps.o: dmps.c
frmt.o: frmt.c



drive.o: drive.c drive.h
mbr.o: mbr.c drive.h mbr.h
mkvol.o: mbr.c mbr.h drive.h
dvol.o: mbr.c mbr.h drive.h

%.o: %.c
	$(CC) $(CFLAGS) -c $< $(INCDIR)

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o $(BINARIES)
realclean: clean
	$(RM) vdiskA.bin vdiskB.bin
depend :
	$(CC) -MM $(INCDIR) *.c
