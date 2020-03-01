#ifndef MBR
#define MBR

#include "drive.h"

#define MBR_MAGIC 42
#define MAXPART 8

enum PartType{BASE, ANNEXE, AUTRE};

extern struct mbr_s mbr;

struct partition_s{ 
	unsigned int cylinder;							
	unsigned int sector;			
	unsigned int nbblocs;
	enum PartType partType ;
};

struct mbr_s{
	struct partition_s tab[MAXPART]; /* un tableau de MAXPART contient les partions */
	unsigned int size;
	unsigned int magic;
};

void load_mbr();
void save_mbr ();
void read_bloc(unsigned int vol, unsigned int nbloc, unsigned char *buffer);
void write_bloc(unsigned int vol, unsigned int nbloc, const unsigned char *buffer);
void format_vol(unsigned int vol,unsigned int nbloc);

char* display_type_vol(enum PartType type);
void display_volumes();



#endif
