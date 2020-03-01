#include <stdio.h>
#include <assert.h> 
#include "try.h"

int try(struct ctx_s * c,func_t f , int arg)
{
 asm ("movl %%esp,%0" "\n\t" 
      "movl %%ebp, %1"
	 : "=r"(c->esp), "=r"(c->ebp) 
	 :  
         : );
	c->magic=MAGIC;
	return f(arg);
}


int throw(struct ctx_s * c,int r)
{
	static int sr ;
	sr=r;
	assert(c->magic ==MAGIC);
	asm ("movl  %0, %%esp" "\n\t" 
	      "movl %1 ,%%ebp"
	:  
	:  "r"(c->esp), "r" (c->ebp)
	: );
	return sr;
}
