#ifndef SB
#define SB

#include "mbr.h"

#define MAGIC 0xACCD1001
#define MAXBLOCKS 32

extern unsigned int current_vol;


struct superbloc_s
{
	int magic;
	int numeroSerie;
	char nom[32]; /* un nom de 32 bits maximum */ 
	unsigned nfirstfree;
	unsigned nfree;
};


struct free_bloc_s 
{
	unsigned size;
	unsigned next;
};



void init_super(unsigned int vol);
int load_super(unsigned int vol);
void save_super();
unsigned int new_bloc();
void free_bloc(unsigned int bloc);
float taux_occupation();


#endif
