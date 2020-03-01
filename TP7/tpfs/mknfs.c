#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "superbloc.h"
#include "mbr.h"

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
	int m=create_volume(3, 3, 11, 1);
	printf("je suis i , le num volume courant %d\n",m);
	int j=load_super(m);
	if(j==0) printf("le load est bien fait\n");
	display_volumes();
   	
	save_mbr();
	init_super(m);
	printf("Taux d'occupation : %f%\n", taux_occupation());
	while (new_bloc() > 0)
	{
		printf("Création d'un nouveau bloc\n");
	}
	
	if(new_bloc() == 0)
	{
	printf("##########################################\n");
	printf("Le disque est plein, Il n'ya plus de blocs libres\n");
	printf("##########################################\n");
	}
	printf("Taux d'occupation : %f%\n", taux_occupation());
	/* generer un nombre aleatoire */ 
	free_bloc(5);
	printf("Free du bloc 5\n");
	free_bloc(8);
	printf("Free du bloc 8\n");
	save_super();
	
display_volumes();
	printf("Taux d'occupation : %f%\n", taux_occupation());
	
		
	
	exit(EXIT_SUCCESS); 
}
