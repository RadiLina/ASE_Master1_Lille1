#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>



#define N 100                         /* nombre de places dans le tampon */

#define MAGIC 0x42424242

typedef void func_t (void*);


/* Declaration de la structure du semaphore */
struct sem_s {
 int n;
 struct ctx_s * ctxs;
};
struct sem_s mutex, vide, plein;

void sem_init(struct sem_s *sem, unsigned int val);
void sem_down(struct sem_s *sem);
void sem_up(struct sem_s *sem);
void start_sched();
int create_ctx(int stack_size, func_t f, void *args);

void producteur (void);
void consommateur (void);

/* static int *tampon;                   /* declaration du tampon */

static int cpt=0;




int main(int argc, char *argv[]) 
{
	sem_init(&mutex, 1);                /* controle d'acces au tampon */
	sem_init(&vide, N);             /* nb de places libres */
	sem_init(&plein, 0);        /* nb de places occupees */                       
    	/* tampon = malloc(N*sizeof(int));      /* initialisation du tampon */ 
	create_ctx(16384, producteur, NULL);
	create_ctx(16384, consommateur, NULL);
	start_sched();

	exit(EXIT_SUCCESS);
}




void producteur (void)
{
  int objet;

  while (1) {
    /*produire_objet(&objet);            produire l'objet suivant */
    sem_down(&vide);                  /* dec. nb places libres */
    sem_down(&mutex);                 /* entree en section critique */
    /* mettre_objet(objet);              mettre l'objet dans le tampon */
    sem_up(&mutex);                   /* sortie de section critique */
    sem_up(&plein);                   /* inc. nb place occupees */
  }
}

void consommateur (void)
{
  int objet;

  while (1) {
    sem_down(&plein);                 /* dec. nb emplacements occupes */
    sem_down(&mutex);                 /* entree section critique */
    retirer_objet(&objet);           /* retire un objet du tampon */
    sem_up(&mutex);                   /* sortie de la section critique */
    sem_up(&vide);                    /* inc. nb emplacements libres */
    utiliser_objet();            /* utiliser l'objet */
  }
}



/* permet de mettre un objet dans le tampon */
void mettre_objet(){
	cpt++;
} 

/* retirer un objet du tampon */
void retirer_objet (){
	cpt--;
}  
 
/* utiliser l'objet retirer */
void utiliser_objet(){
printf("L'objet a été utilisé"); 	
}

/* permet de produire un objet dans le tampon
void produire_objet(&objet){
  int x=5;
  objet=x;
  printf("L'objet a été produit, sa valeur est de %d\n", x);
}
*/

