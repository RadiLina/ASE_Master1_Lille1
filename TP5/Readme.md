###### lina RADI

# ASE_TP5
### Première couche logicielle : accès au matériel


## Compilation
Lancer la commande ```make``` compilera un exécutable "dmps" et "frmt".

## Explication
```dmps``` (dump sector): sert pour l'affichage d'un secteur,le programme prend deux arguments en paramètres, un numéro de piste et un numéro de secteur et affiche le contenu, octet par octet, du secteur.

```frmt``` : sert pour le formatage d'un disque,il s'agit d'un programme qui détruit entièrement le contenu d’un disque physique en formatant chaque secteur du disque. 

## Exécution
./dmps numero cylindre numero secteur
./frmt numero cylindre numero secteur nombre secteurs




