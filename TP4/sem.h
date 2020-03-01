#include <stdlib.h>
#include <stdio.h>
#include <assert.h>



/* ajout de l'etat BLOCKED*/
enum STATUS {READY, ACTIVABLE,TERMINATED,BLOCKED};


typedef void func_t (void*);

/*L'etend de la structure ctx_s */
struct ctx_s {
	void *rsp;
	void *rbp;
	int magic;
	void * args;
	enum STATUS status;
	func_t f;
	char *stack;
	struct ctx_s * next; /*pointeur vers le prochain contexte*/
	struct ctx_s * sem_next; /* pointeur vers le prochain contexte bloqué */
};

int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args);
int create_ctx(int stack_size, func_t f, void *args);

void switch_to_ctx(struct ctx_s *ctx);
void yield();
void start_sched();

void sem_init(struct sem_s *sem, unsigned int val);
void sem_down(struct sem_s *sem);
void sem_up(struct sem_s *sem);


