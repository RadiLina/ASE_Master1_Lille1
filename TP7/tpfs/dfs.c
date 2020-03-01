#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "superbloc.h"

static void
empty_it()
{
    return;
}

int main() 
{
	int i;
	/* init hardware */
	    if(init_hardware("hardware.ini") == 0) 
	    {
			fprintf(stderr, "Error in hardware initialization\n");
			exit(EXIT_FAILURE);
	    }

	    /* Interreupt handlers */
	    for(i=0; i<16; i++)
		IRQVECTOR[i] = empty_it;

	
 	load_mbr(); 
	save_mbr();
	/* creer un volume aleatoirement */
	int num_vol= create_volume(3, 3, 11, 1);
	printf("NUM VOL %d%\n",num_vol);
	load_super(num_vol-1);
	save_super(); 
	display_volumes();
	printf("Taux d'occupation : %f%\n", taux_occupation());
	free_bloc(1); 
	free_bloc(2); 
	printf("Taux d'occupation : %f%\n", taux_occupation());
}
