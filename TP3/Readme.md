###### lina RADI

# ASE_TP3
### Gestion de contextes : ordonnancement, ordonnancement sur interruptions


## Compilation
Lancer la commande ```make``` compilera un exécutable "create_ctx" et "ordonnanceur".

## Exécution
"./create_ctx" executera le premier programme

"./ordonnanceur" executera l'ordonnanceur

##### Explication pour le deroulement
Dans le programme "create_ctx" le deroulement des fonctions se fait par l'ordonnanceur qui choisit le prochain programme a executé c'est à dire avec un ```partage volontaire du processeur``` par un appel explicite à la fonction "yield()"

Par contre dans le programme "ordonnanceur" l'ordonnancement se fait sur interruptions c'est à dire ```ordonnancement préemptif avec partage involontaire du processeur``` . L’ordonnanceur va être capable d’interrompre le contexte en cours d’exécution et de changer de contexte


##### Remarque 
Pour arreter l'execution faites un ```Cntrl-C```  
