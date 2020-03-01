#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "superbloc.h"
#include "mbr.h"
#include <assert.h>


struct superbloc_s superBlock;
unsigned current_volume;


/* Initialise le super bloc et le volume de numero vol */ 
void init_super(unsigned int vol)
{
	unsigned char buf[HDA_SECTORSIZE];
	struct free_bloc_s bloc;	
	
	/* Initialisation du superbloc */
	superBlock.magic = MAGIC;
	superBlock.numeroSerie = 1;
	strncpy(superBlock.nom, "block", 32);
	superBlock.nfirstfree = 1;
	superBlock.nfree= mbr.tab[current_volume].nbblocs - 1;
	
	/* ecriture du superbloc */
	
	memcpy(buf, &superBlock,HDA_SECTORSIZE);
	write_bloc(vol, 0, buf); /* le super bloc se trouve au bloc 0 */

	/* creation du 1er bloc libre */
	bloc.size = MAXBLOCKS-1;
	bloc.next = -1; /* pour indiquer qu'il n'ya pas de serie apres */
		
	/* ecriture du 1er bloc libre */
	memcpy(buf, &bloc, HDA_SECTORSIZE);
	write_bloc(vol, 1, buf); /* a l'initialisation, le premier bloc libre est le premier bloc  */
}

int load_super(unsigned int vol)
{
	unsigned char buf[HDA_SECTORSIZE];

	current_volume = vol;
	/* Lire le super 0 block du volume demandé */
	read_bloc(vol, 0, buf);
	memcpy(&superBlock, buf, sizeof(struct superbloc_s));
	if (superBlock.magic == MAGIC)
		return 0;
	return -1;
}

void save_super()
{
	 unsigned char buf[HDA_SECTORSIZE];
	
	memcpy(buf, &superBlock, sizeof(superBlock));
	write_bloc(current_volume, 0, buf);
}

/* alloue un bloc */ 
unsigned int new_bloc()
{
	unsigned char buf[HDA_SECTORSIZE];
	struct free_bloc_s* bloc;
	unsigned res;
	
	/* tester s'il n'ya plus de blocs libres */ 
	if (superBlock.nfree == 0)
		return 0;
	assert(superBlock.nfirstfree);

	read_bloc(current_volume, superBlock.nfirstfree, buf);
	bloc = (struct free_bloc_s*) buf;
	res = superBlock.nfirstfree;
	if (bloc->size > 1)
	{
		superBlock.nfirstfree++;
		bloc->size--;
		write_bloc(current_volume, superBlock.nfirstfree, buf);
	} else {
		superBlock.nfirstfree = bloc->next;
	}
	superBlock.nfree--;
	save_super();
	return res;
}

/* desalloue un bloc */ 
void free_bloc(unsigned int bloc)
{
	
	int old_first = superBlock.nfirstfree;
	
	unsigned char buf[HDA_SECTORSIZE];
	struct free_bloc_s * fb=buf;
	fb->size = 1;
	fb->next = old_first;
	write_bloc(current_volume, bloc, buf);
	superBlock.nfirstfree = bloc;
	superBlock.nfree++;
	save_super();
}

float taux_occupation()
{
printf("adresse du mbr: %x\n", &mbr);
	/* (mbr.tab[vol].nbblocs-1) : nombre total de blocks dans le volume courant 
	float nb_blocs_total =(float)(mbr.tab[current_volume].nbblocs-1);
	/* nb blocs occupes= nb total blocs - nb blocs libres 
float nb_blocks_occupes= nb_blocs_total -(float)superBlock.nfree;

	return ( (nb_blocks_occupes*100)/nb_blocs_total);*/
	
	float f = superBlock.nfree;
	int nb_blocs_total =(mbr.tab[current_volume].nbblocs-1);
	printf("total blocs (vol=%d) %d\n", current_volume, mbr.tab[0].nbblocs);
	printf("free blocs %f\n", f);
}


