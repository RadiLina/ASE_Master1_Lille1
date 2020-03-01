#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mbr.h"

/* permet de creer un volume d'une taille donnee (-b nombre de blocs) a partir du cylindre/secteur donne (-c, -s) */
static void
empty_it()
{
    return;
}

int main()
{
    int cylinder;
    int sector;
    int nbblocs;
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
    printf("Saisir le nombre de blocs :\n");
    scanf("%i", &nbblocs);
    printf("Saisir le numero du 1er cylindre:\n");
    scanf("%i", &cylinder);
    printf("Saisir le numero du 1er secteur:\n");
    scanf("%i", &sector);
    printf("Choisir le type du volume (0- Base\n1- Annexe\n2- Autre:\n");
    scanf("%i", &i);
          
    create_volume(cylinder,sector, nbblocs, i);
    save_mbr();
    exit(EXIT_SUCCESS);
}
