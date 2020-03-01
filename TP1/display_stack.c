#include <stdio.h>

void foo();
void bar(int x, int y);
//on se sert d'une macro pour copier le contenu des registres %r vers des variables , pour les afficher, sa permet d'avoir un code propre et plus lisible;
#define MA_MACRO {\
    int x, y;\
    asm ("movl %%esp,%0" "\n\t" "movl %%ebp, %1"\
	 : "=r"(x), "=r" (y) /* registre vers varibles (arg sortie) */\
	 :  /* variables vers registres (arg entree)*/ \
         : );\
    printf("le sommet de la pile d’exécution 'esp' vaut:  %d\n",x);\
    printf("la base de la pile d’exécution 'ebp' vaut:  %d \n",y);\ 
}


int main(void){
  int var1,var2; //deux variables dans la fonction main 
  printf("\n");
  printf("~~ La fonction main ~~\n");
  MA_MACRO;
  //appel recursif
  foo();
  bar(&var1,&var2);
     
}                                                           
  
//Une fonction foo
void foo() {
  int var_f1,var_f2;
  printf("\n");
  printf("~~ La fonction foo ~~\n");
  printf("L'@ variable locale var_f vaut : %p\n", &var_f1);
  MA_MACRO;
  //appel imbriquè
  bar(var_f1,var_f2); //envoi des variables en parametres
}


//Une fonction bar
void bar(int x,int y) {
  int var_b;
  printf("\n");
  printf("~~ La fonnction bar ~~\n");
  MA_MACRO;
  printf("L'@ de la variable locale var_b vaut :%p\n", &var_b);
  printf("Les @ des paramètres x vaut :%p, y vaut: %p\n", &x, &y);
		
}  

 
