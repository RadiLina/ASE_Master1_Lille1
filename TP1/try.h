typedef int (*func_t)(int);
struct ctx_s{
	int esp;
	int ebp;
	int magic;
} ;

#define MAGIC 0x42424242 

int try(struct ctx_s * pctx, func_t f,int arg);
int throw(struct ctx_s * pctx,int r);


