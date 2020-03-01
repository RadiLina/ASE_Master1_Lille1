/* ------------------------------
   $Id: tmr.c 69 2007-05-11 11:54:15Z phm $
   ------------------------------------------------------------

   Program a timer

   Philippe Marquet, march 2007

   A minimal example of a program using the timer interface.

*/
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include <unistd.h>
#include "hardware.h"
#include "hwconfig.h"




#define MAGIC 0x42424242


static struct ctx_s *ctx_courant = NULL;
static struct ctx_s *ctxs = NULL;
struct ctx_s ping_ctx;
struct ctx_s pong_ctx;

typedef void (*func_t) (void*);

enum STATUS {READY, ACTIVABLE,TERMINATED};

/*L'etend de la structure ctx_s (ajout d'un pointeur vers le prochain contexte )*/
struct ctx_s {
	void *rsp;
	void *rbp;
	int magic;
	void * args;
	enum STATUS status;
	func_t f;
	char *stack;
	struct ctx_s * next; /*pointeur vers le prochain contexte*/
};



/*declaration des fonctions*/
int create_ctx(int stack_size, func_t f, void *args);
void yield();
void init_ctx(struct ctx_s * ctx,int stacksize,func_t f,void * args);
void switch_to_ctx(struct ctx_s *ctx);
void start_sched();
void irq_disable();
void irq_enable();
static void timer_it();
void ping(void * args);
void pong(void * args);


/* la fonction main */
int main(int argc, char *argv[])
{
	create_ctx(16384, ping, NULL);
	create_ctx(16384, pong, NULL);
	start_sched();
	while(1){pause();}

	exit(EXIT_SUCCESS);
}









/* la fonction d'initialisation d'un contexte */
void init_ctx(struct ctx_s * ctx,int stacksize,func_t f,void * args)
{
	assert(ctx);
	ctx->magic =MAGIC;
	ctx->f =f;
	ctx->args = args;
	ctx->stack =malloc(stacksize);
	ctx->rsp = ctx->stack + stacksize-4; /* 32 bits <=> 4 */
	ctx->rbp = ctx->stack +stacksize-4;
	ctx->status=READY;
}

/* La fonction switch_to_ctx , permet de changer le contexte courant vers celui passer en parametre */
void switch_to_ctx(struct ctx_s *ctx)
{
	/* static struct ctx_s * stable_ctx;  
	stable_ctx= ctx; */

	assert(ctx->magic ==MAGIC && ctx->status!=TERMINATED);
	
	irq_disable();
	if(ctx_courant!=NULL){  
        asm("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
        : "=r" (ctx_courant->rsp)
        ,"=r" (ctx_courant->rbp));

	}


	ctx_courant=ctx;
	irq_enable();
	/* restaurer le nouveau contexte "stable_ctx" */
	asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
	    :
	    : "r" (ctx_courant->rsp)
	    ,"r" (ctx_courant->rbp));

	

	if(ctx_courant->status==READY){
	ctx_courant->status=ACTIVABLE;
	ctx_courant->f(ctx_courant->args);
	ctx_courant->status=TERMINATED;
	yield();
	}else{
	return;
	}

}

/* Creation du contexte et ajout dans la liste des contextes*/
int create_ctx(int stack_size, func_t f, void *args)
{
	struct ctx_s* nv_ctx;
	nv_ctx = (struct ctx_s*)malloc(sizeof(struct ctx_s));
	init_ctx(nv_ctx, stack_size, f, args);
	
	if (ctxs) /*il existe deja des elems*/
	{
		nv_ctx->next = ctxs->next;
		ctxs->next = nv_ctx;
	}
	else /*un seul element*/
	{

		ctxs = nv_ctx;
		ctxs->next = nv_ctx;
	}
	irq_enable();
	return 1;
}

/* Met a jour la liste des contextes et passe au contexte suivant*/
void yield()
{
	if (ctx_courant)
	{
		struct ctx_s *tmp;
	
		while ((ctx_courant->next->status == TERMINATED) && (ctx_courant->next != ctx_courant))
		{
			tmp = ctx_courant->next;
			ctx_courant->next = ctx_courant->next->next;
			free(tmp->stack);
			free(tmp);
		}
		if (ctx_courant->next->status != TERMINATED)
		{
			
			switch_to_ctx(ctx_courant->next);
		}
		else
		{
			exit(0);
		}
	}
	else
	{
		assert(ctxs);
		switch_to_ctx(ctxs);
	}
}

static void empty_it(void)
{
    return;
}

static void timer_it() {
    static int tick = 0;
    fprintf(stderr, "hello from IT %d\n", ++tick);
_out(TIMER_ALARM,0xFFFFFFFE);
    yield();
    
}


/*la fonction start_schedule*/
void start_sched(){
  unsigned int i;
    if (init_hardware(INIFILENAME) == 0) {
    fprintf(stderr, "Error in hardware initialization\n");
    exit(EXIT_FAILURE);
    }

    /* dummy interrupt handlers */
    for (i=0; i<16; i++)
    IRQVECTOR[i] = empty_it; /*initialisation du tableau d'iterruptions avec des fonctions vides*/

    /* program timer */
    IRQVECTOR[TIMER_IRQ] = timer_it;  /*initialiser le tableau IRQVECTOR avec la fonction qui appel yield */
    _out(TIMER_PARAM,128+64+32 + 8); /* reset + alarm on + 8 tick */
    _out(TIMER_ALARM,0xFFFFFFFE);  /* alarm at next tick*/

    /* allows all IT */
    _mask(1);
    
	
}
void irq_disable() {
    _mask(15); /*Désactiver les interruptions*/
}

void irq_enable() {
    _mask(1); /* Réactiver les interruptions*/
}

void ping(void *args) {
	while(1) {
		printf("A");
		printf("B");
		printf("C");
	}
}

void pong(void *args) {
	while(1) {
		printf("1");
		printf("2");
	}
}
