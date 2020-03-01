#include "sem.h"
#define N 100 						/* nombre de places dans le tampon */

struct sem_s mutex, vide, plein;

static int cpt = 0;

void mettre()
{
	cpt++;
}

void enlever()
{
	cpt--;
}

void producteur (void *arg)
{
	while (1) 
	{
		sem_down(&mutex); 			/* dec. nb places libres */
		sem_down(&vide); 		/* entree en section critique */
		mettre();
		printf("On produit l'objet %d\n", cpt);/* produire l’objet suivant */
		sem_up(&plein); 		/* sortie de section critique */
		sem_up(&mutex); 		/* inc. nb place occupees */
	}
}

void consommateur (void *arg)
{	
	while (1) 
	{
		sem_down(&mutex); 			/* dec. nb emplacements occupes */
		sem_down(&plein); 			/* entree section critique */
		printf("On retire l'objet %d\n", cpt); 	/* retire un objet du tampon */
		enlever();
		sem_up(&vide); 			/* sortie de la section critique */
		sem_up(&mutex); 				/* inc. nb emplacements libres */
	}
}

int main(int argc, char *argv[]) 
{
	sem_init(&mutex, 1); 				/* controle d’acces au tampon */
	sem_init(&vide, N); 				/* nb de places libres */
	sem_init(&plein, 0); 				/* nb de places occupees */	
	create_ctx(16384, producteur, NULL);
	create_ctx(16384, consommateur, NULL);
	start_sched();

	exit(EXIT_SUCCESS);
}
