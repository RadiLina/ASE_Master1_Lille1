#include "drive.h"
#include "mbr.h"
#include <stdio.h>

/*static struct mbr_s mbr;*/

struct mbr_s mbr;

/* Charge le Master boot record */ 
void load_mbr(){
	char buffer[HDA_SECTORSIZE];
	read_sector(0,0,buffer); /* sect 0 , piste 0 contiennent le mbr */ 
	memcpy(&mbr, buffer, sizeof(struct mbr_s)); /*copier dans un structure mbr*/
	/* on regarde si le disque est vierge=ne contient pas mbr */
	if (mbr.magic != MBR_MAGIC){
		/* Initialisation */
		mbr.size = 0;
		mbr.magic = MBR_MAGIC;
	}
}

/* Sauvegarde mbr */
void save_mbr (){
	char buffer[HDA_SECTORSIZE];
	memcpy(buffer, &mbr, sizeof(struct mbr_s));
	write_sector(0, 0, buffer);
}



/* Retourne le numero de cylinder du bloc */
int cyl_of_bloc(unsigned int vol, unsigned int nbloc){
	struct partition_s p=mbr.tab[vol];
	int sectDebut=p.sector;
	int cylDebut=p.cylinder;
	return cylDebut + ((nbloc+sectDebut)/8);
}

/* Retourne le numero de secteur du bloc */
int sec_of_bloc(unsigned int vol, unsigned int nbloc)
{
	struct partition_s p=mbr.tab[vol];
	int sectDebut=p.sector;
	int cylDebut=p.cylinder;
	return ((nbloc+sectDebut)%8);
}

/* lit un bloc */ 
void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer)
{
	int cylinder = cyl_of_bloc(vol, nbloc);
	int sector = sec_of_bloc(vol, nbloc);
	read_sector(cylinder, sector, buffer);
}

/* ecrit dans un bloc */
void write_bloc(unsigned int vol, unsigned int nbloc, const unsigned char *buffer)
{
	int cylinder = cyl_of_bloc(vol, nbloc);
	int sector = sec_of_bloc(vol, nbloc);
	write_sector(cylinder, sector, buffer);
}

/* format un bloc */
void format_vol(unsigned int vol,unsigned int nbloc){
	int cylinder = cyl_of_bloc(vol, nbloc);
	int sector = sec_of_bloc(vol, nbloc);
	int nsector = mbr.tab[vol].nbblocs;
	format_sector(cylinder, sector, nsector, 0);
}

/* Ajout de fonctions pour la creaion et l affichage d'un volume */ 

/*
 * size=1
 * 0: <== ici
 * 1
 * 2
 * 3
 */

/* cree un volume */ 
int create_volume(unsigned int cylinder, 
				unsigned int sector, 
				unsigned int nbblocs, 
				enum PartType type){
	if (mbr.size == MAXPART)
	{
		fprintf(stderr, "Impossible de créer un nouveau volume,il n'ya plus d'espace \n");
	} 
	else
	{

		struct partition_s newVol;
		newVol.cylinder=cylinder;
		newVol.sector= sector;
		newVol.nbblocs=nbblocs;
		newVol.partType=type;
		

		mbr.tab[mbr.size] = newVol; /* Ajouter la nouvelle partition(volume) cree dans le mbr */ 
		int tmp = mbr.size;
		mbr.size++;
		return tmp; /* return mbr.size - 1 */
	}
}



char* display_type_vol(enum PartType type)
{
	switch(type){
		case BASE: return "Base";
		case ANNEXE: return "Annexe";
		default: return "Autre";
	}
}
/* afficher le(s) volune(s) */
void display_volumes()
{
	int i;
printf("adresse du mbr: %x\n", &mbr);
	printf("Volume|Cylindre|Secteur|Nb blocs|Type\n-------------------------------------------------\n");
	for (i=0; i<mbr.size; i++){
		printf("sda%d\t%d\t%d\t%d\t%s\n", 
			i,
			mbr.tab[i].cylinder,
			mbr.tab[i].sector,
			mbr.tab[i].nbblocs,
			display_type_vol(mbr.tab[i].partType));
	}
}


