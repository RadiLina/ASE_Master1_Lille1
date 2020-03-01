#include "drive.h"


static void
empty_it()
{
    return;
}

int
main(int argc, char **argv)
{
    unsigned int i, j, sectorsize,sector, cylinder, nbsector;
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

    if (argc == 4)
    {
	/* récuperer le numéro du cylindre */
        cylinder = (unsigned int)atoi(argv[1]);
	/* récuperer le numéro du secteur */
        sector = (unsigned int)atoi(argv[2]);
	/* récuperer le nb de secteurs */
        nbsector = (unsigned int)atoi(argv[3]);

        _out(HDA_CMDREG,CMD_DSKINFO);
        sectorsize=_in(HDA_DATAREGS+4)<<8;
    	sectorsize+=_in(HDA_DATAREGS+5);
    	buffer=malloc(sectorsize);
    	
        for (j=0; j < nbsector; j++)
        {
    	    read_sector(cylinder,sector,buffer);
            format_sector(cylinder,sector++,1,0);
            dump_sector(cylinder,sector);
        }
	printf("\nLes données de %d secteurs du cylindre %d ont été formatées, le nv contenu est: \n",nbsector, cylinder);
        
    }
    else 
    {
        printf("Il y'a une erreur \n");
    }

    /* and exit! */
    exit(EXIT_SUCCESS);
}
