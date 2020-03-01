#include "drive.h"

static void
empty_it()
{
    return;
}

int
main(int argc, char **argv)
{
    unsigned int i,sectorsize, sector, cylinder;
    unsigned char* buffer;
    
    /* init hardware */
    if(init_hardware("hardware.ini") == 0) 
    {
		fprintf(stderr, "Error in hardware initialization\n");
		exit(EXIT_FAILURE);
    }

    /* Interreupt handlers */
    for(i=0; i<16; i++)
	IRQVECTOR[i] = empty_it;

    /* Allows all IT */
    _mask(1);

    if (argc == 3)
    {
	/* récuperer le numéro du cylindre */
        cylinder = (unsigned int)atoi(argv[1]);
	/* récuperer le numéro du secteur */
        sector = (unsigned int)atoi(argv[2]);
        
        _out(HDA_CMDREG,CMD_DSKINFO);
        sectorsize=_in(HDA_DATAREGS+4)<<8;
    	sectorsize+=_in(HDA_DATAREGS+5);
        buffer=malloc(sectorsize);
	printf("\nDonnées du cylindre %d et du secteur %d avec read sector\n", cylinder, sector);
	read_sector(cylinder,sector,buffer);
    	dump_sector(cylinder,sector); 
	
      
    } 
    else 
    {
        printf("il y'a une erreur \n");
    }

    /* and exit! */
    exit(EXIT_SUCCESS);
}
