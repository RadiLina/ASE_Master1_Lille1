#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


#define MAGIC 0x42424242

//declaration des structures
static struct ctx_s *ctx_courant = NULL;
static struct ctx_s *ctxs = NULL;
struct ctx_s ping_ctx;
struct ctx_s pong_ctx;

typedef void (*func_t) (void*);

enum STATUS {READY, ACTIVABLE,TERMINATED};

//L'etend de la structure ctx_s (ajout d'un pointeur vers le prochain contexte )
struct ctx_s {
	void *rsp;
	void *rbp;
	int magic;
	void * args;
	enum STATUS status;
	func_t f;
	char *stack;
	struct ctx_s * next; //pointeur vers le prochain contexte
};



//declaration des fonctions
int create_ctx(int stack_size, func_t f, void *args);
void yield();
void init_ctx(struct ctx_s * ctx,int stacksize,func_t f,void * args);
void switch_to_ctx(struct ctx_s *ctx);
void start_shed();
void ping(void * args);
void pong(void * args);


// la fonction main
int main(int argc, char *argv[])
{
	create_ctx(16384, ping, NULL);
	create_ctx(16384, pong, NULL);
	yield();


	exit(EXIT_SUCCESS);
}









//la fonction d'initialisation d'un contexte
void init_ctx(struct ctx_s * ctx,int stacksize,func_t f,void * args)
{
	assert(ctx);
	ctx->magic =MAGIC;
	ctx->f =f;
	ctx->args = args;
	ctx->stack =malloc(stacksize);
	ctx->rsp = ctx->stack + stacksize-4; // 32 bits <=> 4
	ctx->rbp = ctx->stack +stacksize-4;
	ctx->status=READY;
}

//La fonction switch_to_ctx , permet de changer le contexte courant vers celui passer en parametre
void switch_to_ctx(struct ctx_s *ctx)
{
	//static struct ctx_s * stable_ctx; // static pour qu'elle soit
	//stable_ctx= ctx;

	assert(ctx->magic ==MAGIC && ctx->status!=TERMINATED);

	if(ctx_courant!=NULL){  // sauvegarder l'ancien contexte s'il n'est pas null
        asm("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
        : "=r" (ctx_courant->rsp)
        ,"=r" (ctx_courant->rbp));

	}


	ctx_courant=ctx;

	//restaurer le nouveau contexte "stable_ctx"
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

// Creation du contexte et ajout dans la liste des contextes
int create_ctx(int stack_size, func_t f, void *args)
{
	struct ctx_s* nv_ctx;
	nv_ctx = (struct ctx_s*)malloc(sizeof(struct ctx_s));
	init_ctx(nv_ctx, stack_size, f, args);
	if (ctxs) //il existe deja des elems
	{
		nv_ctx->next = ctxs->next;
		ctxs->next = nv_ctx;
	}
	else //un seul element
	{

		ctxs = nv_ctx;
		ctxs->next = nv_ctx;
	}
	return 1;
}

// Met a jour la liste des contextes et passe au contexte suivant
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



void ping(void *args) {
	while(1) {
		printf("A");
		printf("B");
		printf("C");
		yield();
	}
}

void pong(void *args) {
	while(1) {
		printf("1");
		printf("2");
		yield();
	}
}
