#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    display_volumes(); 
    exit(EXIT_SUCCESS);
}
