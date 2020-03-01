#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MAGIC 0x42424242


typedef void func_t (void*);

enum STATUS {TERMINATED, ACTIVABLE, READY, BLOCKED};

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

/* Declaration de la structure du semaphore */
struct sem_s {
 int n;
 struct ctx_s * attente;
};



int init_ctx(struct ctx_s *ctx, int stack_size, func_t f, void *args);
int create_ctx(int stack_size, func_t f, void *args);

void switch_to_ctx(struct ctx_s *ctx);
void yield();
void start_sched();

void sem_init(struct sem_s *sem, unsigned int val);
void sem_down(struct sem_s *sem);
void sem_up(struct sem_s *sem);


