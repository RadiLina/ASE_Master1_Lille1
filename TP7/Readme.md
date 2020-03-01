###### lina RADI

# ASE_TP7
### Troisième couche logicielle 
#### 1re partie : Structure d'un volume (super bloc)

##### Allocateur de blocs,validation. 

``` mknfs ``` : make new filesystem. 

```dfs ``` : display filesystem. 



## Compilation
Lancer la commande ```make``` compilera un exécutable "mknfs" et "dfs".


## Exécution
./mknfs 
> Le programme fait appel à la fonction new_bloc() jusqu’à ce qu’elle retourne une erreur ;
vérifie que le disque est plein ;
itère un nombre aléatoire de fois sur la libération d’un bloc free_bloc() ;
affiche le statut du disque (taille libre) ;
alloue des blocs tant que le disque est non plein et retourne le nombre de blocs ayant pu être alloués.



./dfs
>Ce programme affichera l’état des partitions, et pour la partition courante son taux d’occupation.
