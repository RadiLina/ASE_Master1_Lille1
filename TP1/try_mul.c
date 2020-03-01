#include <stdio.h>
#include <setjmp.h>
#include "try.h"

//static jmp_buf buf;
static struct ctx_s c;

static int mul(int depth)
{
    int i;

    switch (scanf("%d", &i))
    {
    case EOF:
        return 1; /* neutral element */
    case 0:
        return mul(depth + 1); /* erroneous read */
    case 1:
        if (i)
            return i * mul(depth + 1);
        else
            //longjmp(buf,1);
	throw(&c,0);
    }
}

int main()
{
    
    int product=0;

    printf("A list of int, please\n");
    //if(setjmp(buf)==0){
    	//product = mul(0);
    product=try(&c,mul,0);
    printf("product = %d\n", product);
}


