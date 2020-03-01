#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define MAGIC 0x42424242 

typedef void (*func_t) (void*);

enum STATUS {READY, ACTIVABLE,TERMINATED};	

struct ctx_s {
	void *rsp;
	void *rbp;
	int magic;
	void * args;
	enum STATUS status;
	func_t f; 
	char *stack;  
};

struct ctx_s * old_ctx=NULL;  

//declaration des deux structures pour le ping et le pong 
struct ctx_s ping_ctx,pong_ctx;

void init_ctx(struct ctx_s * ctx,int stacksize,func_t f,void * args); 
void switch_to_ctx(struct ctx_s *ctx);
void ping(void * args);
void pong(void * args);

int main(int argc,char ** argv)
{
    init_ctx(&ping_ctx, 16384, ping, NULL);
    init_ctx(&pong_ctx, 16384, pong, NULL);
    switch_to_ctx(&ping_ctx);

    exit(EXIT_SUCCESS);	

}

//la fonction init
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

//La fonction switch_to 
void switch_to_ctx(struct ctx_s *ctx)
{
	static struct ctx_s * stable_ctx; // static pour qu'elle soit 
	stable_ctx= ctx;

	assert(ctx->magic ==MAGIC && ctx->status!=TERMINATED);

	if(old_ctx!=NULL){  // sauvegarder l'ancien contexte s'il n'est pas null
        asm("movl %%esp, %0" "\n\t" "movl %%ebp, %1"
        : "=r" (old_ctx->rsp)    
        ,"=r" (old_ctx->rbp)); 
    
	}
	
	

	//restaurer le nouveau contexte "stable_ctx"
	asm("movl %0, %%esp" "\n\t" "movl %1, %%ebp"
	    :
	    : "r" (stable_ctx->rsp)
	    ,"r" (stable_ctx->rbp));

	
	old_ctx=stable_ctx;
	
	if(stable_ctx->status==READY){
	stable_ctx->status=ACTIVABLE;
	stable_ctx->f(stable_ctx->args);
	stable_ctx->status=TERMINATED;
	}

}

//La fonction ping 
void ping(void * args){
	while(1){
	printf("A\n");
	switch_to_ctx(&pong_ctx);
	printf("B\n");
	switch_to_ctx(&pong_ctx);
	printf("C\n");
	switch_to_ctx(&pong_ctx);
	}
}


//la fonction pong 
void pong(void * args){
	while(1){
	printf("1\n");
	switch_to_ctx(&ping_ctx);
	printf("2\n");
	switch_to_ctx(&ping_ctx);
	}
}



