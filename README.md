![](https://sctechit.files.wordpress.com/2019/11/2508a-main-qimg-f129bd338e0940e14bbbc130fe833e83-c.jpeg?w=960&h=1280&crop=1)



### Description 

Ce simple shell est une interface shell écrite en langage de programmation C qui affiche un prompt * #cisfun$ * .Ce dépôt contient les fichiers nécessaires pour simuler un shell Unix de base avec ses commandes respectives similaires à celles du premier Shell de Ken Thompson.

### Environnement 

OS : Ubuntu-22.04 

Langage : C

éditeur : Visual Studio Code 1.96

ligne directrice : Betty style

### Prescriptions

Simple-shell est conçu pour fonctionner dans l'environnement linux gcc 11.4.0

### Installation compilation et debug 


#### Clone ce depot :
https://github.com/Issercio/holbertonschool-simple_shell.git

#### Compilation : 
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
#### Execution du simple shell :
```
./hsh
```
#### Debug :

Si vous souhaitez analyser les erreurs de votre programme, vous pouvez utiliser valgrind.
```
valgrind --leak-check=full ./hsh
```
### Usage examples:

* echo
```
#cisfun$ echo This is a simple shell 

This is a simple shell
```
* ls

```
#cisfun$ ls
README.md          find_executable.c  handle_error.c  hsh                 path.c       simple_shell.c  str_utils.c  utils.c
execute_command.c  handle_command.c   handle_input.c  man_1_simple_shell  print_env.c  simple_shell.h  test_ls_2 
``` 


* Ctrl+D et Exit
```
#cisfun$ exit

aurelien@DESKTOP-BLAO4BF:~/holbertonschool-simple_shell$
```

### Description du processus :

1) D'abord, le programme crée un processus parent lorsqu'il est lancé par l'utilisateur

2) Ensuite, il vérifie si l'entrée vient d'un terminal avec isatty().Si c'est le cas, il affiche l'invite de commande et attend que l'utilisateur entre une commande.

3) Quand l'utilisateur tape une commande, getline() lit la ligne, puis strtok() la découpe en morceaux. Ensuite, un processus enfant est créé avec fork() pour exécuter la commande. Le processus parent attend que le processus enfant termine avant de continuer.

4) Enfin, la commande est exécutée avec execve(), la mémoire est libérée avec free(), et l'invite de commande réapparaît pour une nouvelle entrée.

### Flowcharts :

# IMAGE

#### Files included in the project :

- **find_executable.c :** Recherche un exécutable dans les répertoires du PATH et retourne son chemin si trouvé, sinon return NULL.

- **handle_error.c :** affiche un message d'erreur fourni en utilisant la fonction perror()

- **hsh :** fichier executable

- **path.c :** recherche un fichier exécutable dans les répertoires du PATH et retourne son chemin complet si trouvé, sinon NULL.

- **simple_shell.c :** crée un shell interactif qui lit et exécute les commandes de l'utilisateur, gère les commandes internes comme exit et env, et continue jusqu'à ce que l'utilisateur quitte.

- **str_utils.c :** Implemente deux fonctions : _strcmp pour comparer deux chaînes de caractères et _strlen pour calculer la longueur d'une chaîne.

- **utils.c :** Implemente trois fonctions : _strdup pour dupliquer une chaîne, _strcpy pour copier une chaîne, et _sprintf pour formater une chaîne avec des arguments supplémentaires.

- **execute_command.c :** recherche l'exécutable d'une commande, l'exécute dans un processus enfant, gère les erreurs d'exécution et attend sa fin avant de libérer la mémoire.

- **handle_command.c :** traite la commande de l'utilisateur, gère les commandes internes (exit, env), tokenise la commande, recherche l'exécutable dans le PATH, exécute la commande dans un processus enfant avec execve(), affiche une erreur si la commande est introuvable, et attend la fin du processus enfant avec wait().

- **handle_input.c :** lit l'entrée de l'utilisateur, la traite en la tokenisant en arguments, vérifie si la commande est exit, et exécute la commande ou continue l'exécution du shell.

- **man_1_simple_shell :** man page

- **print_env.c :** parcourt et affiche toutes les variables d'environnement ligne par ligne.

- **simple_shell.h :** fichier d'en-tête définit les prototypes des fonctions et inclut les bibliothèques nécessaires pour implémenter un shell simple, ainsi que la déclaration de la variable d'environnement environ.

- **test_ls_2 :** contient le chemin absolu du programme ls


### Author :

The Simple Shell project was developped by :



[![Anurag’s github stats](https://github-readme-stats.vercel.app/api?username=Aurelien292)](https://github.com/Aurelien292) ==> L'ensemble des travaux


[![Anurag’s github stats](https://github-readme-stats.vercel.app/api?username=Issercio)](https://github.com/Issercio) ==> L'ensemble des travaux




