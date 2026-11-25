
# Memory maps


Rapport : Analyse d'un programme C – Récursivité et Stack Frames
1. Introduction
Ce programme, développé en langage C, permet d'étudier le fonctionnement de la pile mémoire (Stack) lors de l'exécution de fonctions récursives.
L'objectif est de comprendre comment les variables locales sont stockées en mémoire, comment les adresses mémoire sont utilisées et comment les cadres de pile (Stack Frames) sont créés et supprimés pendant l'exécution d'un programme.
Ces notions sont particulièrement importantes en informatique et en cybersécurité, notamment pour comprendre certaines vulnérabilités liées à la mémoire.
2. Présentation générale du programme
Le programme utilise la bibliothèque standard stdio.h, qui permet notamment d'afficher des informations dans le terminal grâce à la fonction printf().
Il est composé de trois fonctions principales :
main() : point d'entrée du programme.
walk_stack() : réalise les appels récursifs et observe le fonctionnement de la pile.
dump_frame() : affiche les informations concernant les variables locales et leurs adresses mémoire.
Le programme lance une récursivité avec une profondeur maximale de 3.
3. Analyse des fonctions
3.1. Fonction dump_frame()
La fonction dump_frame() reçoit deux paramètres : une étiquette (label) et une profondeur (depth).
Elle déclare trois éléments :
local_int : une variable entière initialisée avec la valeur 100 + depth.
local_buf : un tableau de 16 caractères.
p_local : un pointeur contenant l'adresse mémoire de local_int.
L'instruction &local_int permet de récupérer l'adresse mémoire de la variable.
Le tableau local_buf reçoit une lettre en fonction de la profondeur :
Profondeur
Caractère
0
A
1
B
2
C
3
D

La fonction utilise ensuite plusieurs appels à printf() pour afficher les valeurs et les adresses mémoire.
3.2. Fonction walk_stack()
La fonction walk_stack() constitue la partie principale du programme.
Elle reçoit deux paramètres :
depth : la profondeur actuelle de l'appel.
max_depth : la profondeur maximale autorisée.
Elle commence par créer une variable locale appelée marker, dont la valeur correspond à depth * 10.
Ensuite, elle appelle dump_frame() avec l'étiquette enter pour afficher les informations au début de son exécution.
La récursivité est réalisée grâce à la condition suivante :
if (depth < max_depth)
Lorsque cette condition est vraie, la fonction s'appelle elle-même avec une profondeur augmentée de 1.
La récursivité s'arrête lorsque la profondeur atteint 3.
Enfin, la fonction appelle de nouveau dump_frame(), cette fois avec l'étiquette exit, afin d'afficher les informations avant de terminer son exécution.
3.3. Fonction main()
La fonction main() représente le point de départ du programme.
Elle affiche un message dans le terminal, puis lance la fonction :
walk_stack(0, 3);
Cela signifie que le programme commence avec une profondeur de 0 et une profondeur maximale de 3.
L'instruction return 0; indique que le programme s'est terminé normalement.
4. Fonctionnement de la récursivité
Le programme effectue quatre appels successifs à la fonction walk_stack() :
Appel
Depth
Valeur de marker
walk_stack(0, 3)
0
0
walk_stack(1, 3)
1
10
walk_stack(2, 3)
2
20
walk_stack(3, 3)
3
30

Une fois la profondeur maximale atteinte, les appels commencent à se terminer dans l'ordre inverse :
walk_stack(3, 3)
walk_stack(2, 3)
walk_stack(1, 3)
walk_stack(0, 3)
Ce fonctionnement correspond au principe LIFO (Last In, First Out), c'est-à-dire que le dernier élément ajouté est le premier à être retiré.
5. Compréhension de la pile mémoire (Stack)
La pile mémoire est une zone de mémoire utilisée notamment pour gérer les appels de fonctions.
Lorsqu'une fonction est appelée, un cadre de pile (Stack Frame) est généralement utilisé pour conserver les informations nécessaires à son exécution.
Dans cet exemple, chaque appel récursif de walk_stack() possède ses propres variables locales, notamment marker.
Les variables locales de dump_frame() sont également créées pendant l'exécution de cette fonction.
Les adresses affichées par printf() permettent d'observer l'emplacement de ces variables en mémoire.
Il est important de noter que les adresses peuvent varier selon le système, le compilateur, l'architecture et les options de compilation.
6. Intérêt pour la cybersécurité
L'étude de ce programme permet de comprendre plusieurs notions fondamentales en cybersécurité :
Stack Memory : comprendre le fonctionnement de la pile mémoire.
Stack Frames : comprendre comment les appels de fonctions sont organisés.
Pointeurs : manipuler et comprendre les adresses mémoire.
Variables locales : comprendre leur durée de vie et leur utilisation.
Récursivité : analyser les appels successifs d'une fonction.
Ces connaissances sont utiles pour étudier certaines vulnérabilités, notamment les dépassements de tampon (Buffer Overflow), les attaques de type Stack Smashing et les mécanismes de protection comme les Stack Canaries et l'ASLR.
7. Conclusion
Ce programme constitue un exemple pratique pour comprendre le fonctionnement de la pile mémoire en langage C.
Grâce à la récursivité, il permet d'observer la création et la fin des appels de fonctions, ainsi que l'utilisation des variables locales et des pointeurs.
L'affichage des adresses mémoire permet également de mieux comprendre l'organisation de la mémoire pendant l'exécution.
En conclusion, cet exercice représente une première étape importante dans l'apprentissage de la programmation système et dans la compréhension des vulnérabilités mémoire rencontrées en cybersécurité.


Rapport : Analyse d'un programme C – Allocation dynamique et fuite mémoire (Heap)
1. Introduction
Ce programme, développé en langage C, permet d'étudier le fonctionnement de la mémoire dynamique (Heap), notamment l'allocation, l'utilisation et la libération de mémoire.
L'objectif est de comprendre comment les structures de données peuvent être créées dynamiquement, comment les fonctions malloc() et free() permettent de gérer la mémoire et comment une mauvaise gestion de cette mémoire peut provoquer une fuite mémoire (Memory Leak).
Ces notions sont importantes en programmation système et en cybersécurité, car une mauvaise gestion de la mémoire peut entraîner des dysfonctionnements, une dégradation des performances et certaines vulnérabilités.
2. Présentation générale du programme
Le programme utilise deux bibliothèques principales :
stdio.h : permet d'afficher des informations dans le terminal grâce à printf().
stdlib.h : permet d'utiliser les fonctions de gestion de mémoire dynamique, notamment malloc() et free().
Le programme est composé de trois éléments principaux :
La structure Person : représente une personne avec un nom et un âge.
La fonction person_new() : crée une personne et alloue dynamiquement la mémoire nécessaire.
La fonction person_free_partial() : permet de libérer une partie de la mémoire associée à une personne.
La fonction main() crée deux personnes, Alice et Bob, puis réalise différentes opérations de libération de mémoire. Le programme contient volontairement une fuite mémoire concernant Alice.
3. Analyse du programme
3.1. La structure Person
typedef struct Person
{
    char *name;
    int age;
} Person;
Cette structure permet de stocker les informations d'une personne.
Elle contient deux membres :
name : un pointeur vers une chaîne de caractères contenant le nom.
age : un entier représentant l'âge de la personne.
Le mot-clé typedef permet d'utiliser directement le nom Person pour désigner cette structure, sans devoir écrire struct Person à chaque utilisation.
3.2. La fonction person_new()
static Person *person_new(const char *name, int age)
Cette fonction permet de créer une nouvelle personne en utilisant la mémoire dynamique.
Elle reçoit deux paramètres :
name : le nom de la personne.
age : son âge.
La première allocation mémoire est réalisée avec :
Person *p = (Person *)malloc(sizeof(Person));
Cette instruction réserve dynamiquement un espace mémoire suffisant pour stocker une structure Person.
Si l'allocation échoue, malloc() retourne NULL. Le programme vérifie ce cas :
if (!p)
    return NULL;
Ensuite, la fonction calcule la longueur du nom en parcourant la chaîne de caractères jusqu'au caractère de fin '\0'.
Une seconde allocation est réalisée :
p->name = (char *)malloc(len + 1);
Cette allocation permet de réserver de la mémoire pour stocker le nom de la personne ainsi que le caractère de fin de chaîne.
Si cette allocation échoue, la structure précédemment allouée est libérée avec free(p) avant de retourner NULL.
Le nom est ensuite copié caractère par caractère dans la mémoire allouée.
Enfin, l'âge est attribué à la structure :
p->age = age;
La fonction retourne un pointeur vers la structure créée.
3.3. La fonction person_free_partial()
static void person_free_partial(Person *p)
{
    if (!p)
        return;

    free(p);
}
Cette fonction permet de libérer la mémoire occupée par la structure Person.
Elle commence par vérifier si le pointeur est valide.
Si le pointeur vaut NULL, la fonction ne réalise aucune opération.
Sinon, elle utilise :
free(p);
Cette instruction libère la mémoire occupée par la structure.
Cependant, cette fonction ne libère pas la mémoire utilisée par le champ name, qui a été allouée séparément.
Cela signifie que si la chaîne de caractères est encore allouée, la libération de la structure seule ne suffit pas à libérer l'ensemble de la mémoire utilisée.
Cette particularité constitue l'un des problèmes étudiés dans ce programme.
4. Analyse de la fonction main()
La fonction main() représente le point d'entrée du programme.
Au début, deux pointeurs sont déclarés :
Person *alice = NULL;
Person *bob = NULL;
Ils sont initialisés à NULL afin d'éviter de contenir des adresses non initialisées.
Le programme affiche ensuite un message indiquant qu'il s'agit d'un exemple d'allocations mémoire et de fuite mémoire.
4.1. Création des personnes
alice = person_new("Alice", 30);
bob = person_new("Bob", 41);
Ces instructions permettent de créer deux structures :
Personne
Nom
Âge
Alice
Alice
30
Bob
Bob
41

Chaque personne nécessite deux allocations dynamiques :
Une allocation pour la structure Person.
Une allocation pour la chaîne de caractères name.
Le programme effectue donc quatre allocations dynamiques au total lorsque les deux créations réussissent.
4.2. Vérification des allocations
if (!alice || !bob)
Cette condition vérifie si l'une des deux créations a échoué.
Si Alice ou Bob n'a pas pu être créé, le programme libère les structures qui ont pu être allouées avant de quitter.
Cependant, la fonction person_free_partial() ne libère que la structure Person et non la chaîne name.
Dans le chemin d'erreur, si une personne a été créée avec succès, cette fonction peut donc laisser une allocation de chaîne de caractères non libérée.
5. Affichage des adresses mémoire
printf("  alice=%p name=%p age=%d\n",
       (void *)alice, (void *)alice->name, alice->age);
Cette instruction affiche plusieurs informations concernant Alice :
L'adresse mémoire de la structure Person.
L'adresse mémoire de la chaîne de caractères name.
L'âge de la personne.
Le même affichage est réalisé pour Bob.
Les adresses affichées permettent d'observer que la structure et son nom occupent des emplacements mémoire distincts.
La structure contient un pointeur vers la chaîne de caractères, mais le texte du nom est stocké dans une allocation distincte.
Ces adresses peuvent varier d'une exécution à une autre.
6. Libération de la mémoire de Bob
free(bob->name);
free(bob);
Ces deux instructions permettent de libérer correctement les allocations associées à Bob.
La première instruction libère la mémoire utilisée par la chaîne de caractères.
La seconde libère la mémoire utilisée par la structure Person.
Cette opération respecte le principe de libération de toutes les allocations réalisées pour cette personne.
7. Analyse de la fuite mémoire concernant Alice
Le programme utilise ensuite :
person_free_partial(alice);
Cette fonction libère uniquement la structure Person d'Alice.
Elle ne libère pas la mémoire précédemment allouée pour alice->name.
La mémoire contenant la chaîne de caractères « Alice » reste donc allouée, alors que la structure contenant le pointeur vers cette chaîne a été libérée.
Cela provoque une fuite mémoire (Memory Leak).
Une fois la structure libérée, le programme ne conserve plus de pointeur accessible permettant de libérer normalement cette allocation de chaîne.
Cette situation illustre un problème de gestion de mémoire dynamique.
8. Tableau récapitulatif des allocations
Élément
Allocation
Libération
Résultat
Structure Alice
malloc()
free(alice)
Libérée
Nom Alice
malloc()
Non libéré
<span>Fuite mémoire</span>
Structure Bob
malloc()
free(bob)
Libérée
Nom Bob
malloc()
free(bob->name)
Libérée

Le programme réalise quatre allocations dynamiques, mais une allocation n'est pas correctement libérée.
9. Intérêt pour la cybersécurité
L'étude de ce programme permet de comprendre plusieurs notions fondamentales en cybersécurité :
Heap Memory : comprendre le fonctionnement de la mémoire dynamique.
malloc() : apprendre à réserver de la mémoire pendant l'exécution.
free() : comprendre la libération des allocations.
Memory Leak : identifier les allocations oubliées.
Pointeurs : comprendre la manipulation des adresses mémoire.
Structures : organiser les données et les allocations associées.
Les erreurs de gestion mémoire peuvent avoir des conséquences sur la stabilité et la sécurité d'un programme.
Les fuites mémoire peuvent notamment entraîner une consommation croissante de ressources lorsqu'elles se répètent dans un programme exécuté sur une longue durée.
D'autres erreurs de gestion mémoire, telles que les doubles libérations, les utilisations après libération (Use-After-Free) et les corruptions de mémoire, peuvent également avoir des conséquences importantes en cybersécurité.
10. Conclusion
Ce programme constitue un exemple pratique de gestion de la mémoire dynamique en langage C.
Il permet d'observer la création de structures, l'allocation de mémoire avec malloc(), l'utilisation de pointeurs et la libération de mémoire avec free().
L'exemple de Bob montre une libération correcte des allocations associées à une structure et à sa chaîne de caractères.
À l'inverse, l'exemple d'Alice met en évidence une fuite mémoire provoquée par la libération de la structure sans libérer préalablement la chaîne de caractères.
En conclusion, cet exercice souligne l'importance d'une gestion rigoureuse de la mémoire dynamique en C. La maîtrise de ces mécanismes constitue une base essentielle pour la programmation système et l'étude des vulnérabilités mémoire en cybersécurité.

Rapport : Crash example
1. Introduction
Ce programme, développé en langage C, permet d'étudier les erreurs liées à la manipulation des pointeurs et à l'accès à la mémoire.
L'objectif est de comprendre comment une fonction peut retourner un pointeur NULL, pourquoi il est important de vérifier la validité d'un pointeur avant de l'utiliser et quelles sont les conséquences d'un accès mémoire invalide.
Ce programme provoque volontairement une erreur de segmentation (Segmentation Fault) en essayant d'accéder à une zone mémoire à travers un pointeur invalide.
Ces notions sont essentielles en programmation système et en cybersécurité, car les erreurs de manipulation des pointeurs peuvent entraîner des crashs, des dysfonctionnements ou certaines vulnérabilités.
2. Présentation générale du programme
Le programme utilise deux bibliothèques principales :
stdio.h : permet d'afficher des informations dans le terminal grâce à printf().
stdlib.h : permet d'utiliser les fonctions de gestion de mémoire dynamique, notamment malloc() et free().
Il est composé de deux fonctions principales :
allocate_numbers() : permet d'allouer dynamiquement un tableau d'entiers et de le remplir.
main() : initialise les variables, appelle la fonction d'allocation et tente ensuite d'accéder au tableau.
Le programme contient volontairement une erreur : la fonction allocate_numbers() retourne NULL lorsque la taille demandée est inférieure ou égale à zéro, mais le programme tente ensuite d'utiliser ce pointeur sans vérifier sa validité.
3. Analyse de la fonction allocate_numbers()
static int *allocate_numbers(int n)
Cette fonction permet de créer dynamiquement un tableau d'entiers.
Elle reçoit un paramètre :
n : le nombre d'entiers à stocker dans le tableau.
Elle retourne un pointeur de type int *, qui représente l'adresse du tableau créé, ou NULL si l'allocation ne peut pas être réalisée.
3.1. Initialisation des variables
int *arr = NULL;
int i = 0;
Deux variables sont déclarées :
arr : un pointeur destiné à contenir l'adresse du tableau.
i : un compteur utilisé pour parcourir les éléments du tableau.
Le pointeur arr est initialisé à NULL, ce qui signifie qu'il ne pointe initialement vers aucune zone mémoire valide.
3.2. Vérification de la taille demandée
if (n <= 0)
    return NULL;
Cette condition vérifie si la taille demandée est inférieure ou égale à zéro.
Si n est égal à zéro ou négatif, la fonction retourne immédiatement NULL.
Dans ce programme, la variable n est initialisée à zéro dans la fonction main(). Cette condition est donc déclenchée systématiquement lors de l'appel de allocate_numbers().
3.3. Allocation dynamique de mémoire
arr = (int *)malloc((size_t)n * sizeof(int));
Cette instruction permet de réserver dynamiquement une zone mémoire pouvant contenir n entiers.
malloc() : réserve de la mémoire dans le Heap.
sizeof(int) : détermine la taille en octets d'un entier.
(size_t)n : convertit la valeur de n en type size_t, utilisé pour représenter les tailles de mémoire.
Si l'allocation échoue, malloc() retourne NULL.
La fonction vérifie ensuite ce cas :
if (!arr)
    return NULL;
Cette vérification permet de détecter un échec d'allocation.
3.4. Remplissage du tableau
for (i = 0; i < n; i++)
    arr[i] = (i + 1) * 7;
Cette boucle permet de remplir le tableau avec des multiples de 7.
Si n est égal à 5, les valeurs seraient :
Index
Valeur
0
7
1
14
2
21
3
28
4
35

Cependant, dans le programme étudié, cette boucle ne sera jamais exécutée puisque n vaut zéro et que la fonction retourne NULL avant d'atteindre cette partie du code.
4. Analyse de la fonction main()
La fonction main() constitue le point d'entrée du programme.
4.1. Initialisation des variables
int *nums = NULL;
int n = 0;
Deux variables sont déclarées :
nums : un pointeur destiné à recevoir l'adresse du tableau d'entiers.
n : la taille du tableau à créer.
Le pointeur nums est initialisé à NULL.
La variable n est également initialisée à zéro.
4.2. Affichage des informations
printf("crash_example: deterministic NULL dereference (segmentation fault)\n");
printf("  requesting n=%d\n", n);
Ces deux instructions affichent un message dans le terminal.
Le premier message indique que le programme est conçu pour provoquer un déréférencement de pointeur NULL.
Le second affiche la taille demandée, qui est égale à zéro.
4.3. Appel de la fonction allocate_numbers()
nums = allocate_numbers(n);
Cette instruction appelle la fonction allocate_numbers() avec la valeur zéro.
La condition suivante est alors déclenchée dans cette fonction :
if (n <= 0)
    return NULL;
Le pointeur nums reçoit donc la valeur NULL.
À ce stade, aucune allocation dynamique n'a été effectuée.
5. Analyse de l'erreur de segmentation
L'erreur principale du programme se situe dans cette instruction :
nums[0] = 42;
Le programme tente d'écrire la valeur 42 dans le premier élément du tableau.
Cependant, nums contient la valeur NULL puisque la fonction allocate_numbers() a retourné NULL.
L'accès nums[0] nécessite de dereférencer le pointeur pour accéder à une zone mémoire.
Or, le pointeur ne désigne aucune zone mémoire valide appartenant au tableau.
Cette opération constitue un comportement indéfini en C (Undefined Behavior). Dans le contexte de cet exemple, elle provoque généralement un crash du programme, souvent signalé par un Segmentation Fault.
Le programme ne peut donc normalement pas poursuivre son exécution jusqu'à l'affichage suivant :
printf("  nums[0]=%d\n", nums[0]);
6. Analyse de la libération mémoire
free(nums);
Cette instruction est prévue pour libérer la mémoire associée au tableau.
Cependant, dans le programme étudié, l'exécution est généralement interrompue avant d'atteindre cette instruction.
De plus, dans le cas présent, nums vaut NULL et aucune allocation n'a été effectuée.
En C, appeler free() avec un pointeur égal à NULL est autorisé et ne provoque aucune action.
7. Déroulement du programme
Étape
Opération
Résultat
1
Initialisation de n
n = 0
2
Initialisation de nums
nums = NULL
3
Appel de allocate_numbers(0)
La fonction est appelée
4
Vérification de n <= 0
La condition est vraie
5
Retour de la fonction
NULL est retourné
6
Affectation à nums
nums = NULL
7
nums[0] = 42
Déréférencement invalide
8
Exécution
Crash généralement provoqué

8. Intérêt pour la cybersécurité
L'étude de ce programme permet de comprendre plusieurs notions fondamentales en cybersécurité :
NULL Pointer : comprendre ce qu'est un pointeur ne contenant aucune adresse valide.
Déréférencement : comprendre les conséquences de l'accès à la mémoire à travers un pointeur.
Segmentation Fault : comprendre les crashs provoqués par certains accès mémoire invalides.
Allocation dynamique : comprendre les conditions dans lesquelles une fonction peut retourner NULL.
Validation : apprendre à vérifier les retours des fonctions avant leur utilisation.
Les erreurs de manipulation de pointeurs peuvent affecter la stabilité des applications.
Selon le contexte, elles peuvent également être exploitées pour provoquer des interruptions de service ou contribuer à d'autres problèmes de sécurité.
La vérification des pointeurs et la gestion des erreurs constituent donc des pratiques importantes en programmation sécurisée.
9. Correction du programme
Pour corriger le problème, il est nécessaire de vérifier si le pointeur retourné par allocate_numbers() est valide avant de l'utiliser.
Une correction possible consiste à vérifier le retour de la fonction :
nums = allocate_numbers(n);

if (!nums)
{
    printf("Erreur : allocation impossible ou taille invalide\n");
    return 1;
}

nums[0] = 42;
Cette vérification permet d'éviter d'utiliser un pointeur NULL.
Cependant, pour que le programme fonctionne normalement, il faut également attribuer une valeur positive à n, par exemple n = 5, afin que la fonction puisse créer le tableau.
10. Conclusion
Ce programme constitue un exemple pratique de gestion des pointeurs et d'analyse des erreurs mémoire en langage C.
Il permet d'observer comment une fonction peut retourner NULL lorsqu'une taille invalide est demandée et comment l'utilisation d'un pointeur non valide peut entraîner un crash.
L'erreur principale est provoquée par l'accès à nums[0] alors que nums contient NULL.
En conclusion, cet exercice souligne l'importance de vérifier les retours des fonctions, de contrôler les pointeurs avant leur utilisation et de gérer correctement les erreurs en programmation C.
Ces pratiques constituent des bases essentielles pour la programmation système et l'apprentissage de la cybersécurité.

Rapport : Analyse d'un programme C – Aliasing et Use-After-Free
1. Introduction
Ce programme, développé en langage C, permet d'étudier le partage d'une adresse mémoire entre plusieurs pointeurs ainsi que les conséquences de la libération de cette mémoire.
L'objectif est de comprendre le fonctionnement de l'aliasing, c'est-à-dire lorsque plusieurs pointeurs désignent une même zone mémoire, et d'observer les conséquences d'une utilisation de mémoire après sa libération, appelée Use-After-Free (UAF).
Ces notions sont particulièrement importantes en programmation système et en cybersécurité, car les erreurs de gestion des pointeurs et de la mémoire dynamique peuvent provoquer des dysfonctionnements, des crashs ou des vulnérabilités.
2. Présentation générale du programme
Le programme utilise deux bibliothèques principales :
stdio.h : permet d'afficher des informations dans le terminal grâce à printf().
stdlib.h : permet d'utiliser les fonctions de gestion de mémoire dynamique, notamment malloc() et free().
Il est composé de deux fonctions principales :
make_numbers() : alloue dynamiquement un tableau d'entiers et le remplit avec des valeurs.
main() : crée le tableau, utilise deux pointeurs pour accéder à la même zone mémoire, libère la mémoire puis tente de réutiliser cette mémoire.
Le programme illustre volontairement un problème de type Use-After-Free, puisqu'un pointeur est utilisé après la libération de la zone mémoire qu'il désignait.
3. Analyse de la fonction make_numbers()
static int *make_numbers(int n)
Cette fonction permet de créer dynamiquement un tableau d'entiers.
Elle reçoit un paramètre :
n : le nombre d'entiers à stocker dans le tableau.
Elle retourne un pointeur de type int *, qui représente l'adresse du tableau créé, ou NULL si la taille est invalide ou si l'allocation échoue.
3.1. Initialisation des variables
int i = 0;
int *arr = NULL;
Deux variables sont déclarées :
i : un compteur utilisé pour parcourir les éléments du tableau.
arr : un pointeur destiné à contenir l'adresse du tableau.
Le pointeur arr est initialisé à NULL, ce qui permet d'éviter de conserver une adresse non initialisée.
3.2. Vérification de la taille
if (n <= 0)
    return NULL;
Cette condition vérifie si la taille demandée est inférieure ou égale à zéro.
Si la valeur de n est invalide, la fonction retourne NULL et aucune allocation dynamique n'est réalisée.
3.3. Allocation dynamique
arr = (int *)malloc((size_t)n * sizeof(int));
Cette instruction réserve dynamiquement un espace mémoire pouvant contenir n entiers.
malloc() : permet de réserver de la mémoire dans le Heap.
sizeof(int) : permet de connaître la taille d'un entier.
(size_t)n : convertit la valeur de n en type size_t, utilisé pour représenter les tailles de mémoire.
La fonction vérifie ensuite si l'allocation a échoué :
if (!arr)
    return NULL;
Si malloc() retourne NULL, la fonction retourne également NULL.
3.4. Remplissage du tableau
for (i = 0; i < n; i++)
    arr[i] = i * 11;
Cette boucle permet de remplir le tableau avec des multiples de 11.
Dans le programme, n vaut 5.
Le tableau contient donc les valeurs suivantes :
Index
Valeur
0
0
1
11
2
22
3
33
4
44

Une fois le tableau rempli, la fonction retourne le pointeur arr.
4. Analyse de la fonction main()
La fonction main() constitue le point d'entrée du programme.
4.1. Initialisation des variables
int *a = NULL;
int *b = NULL;
int n = 5;
Trois variables sont déclarées :
a : un pointeur destiné à recevoir l'adresse du tableau.
b : un second pointeur.
n : le nombre d'entiers à créer.
Les deux pointeurs sont initialisés à NULL.
La variable n est initialisée à 5, ce qui permet à la fonction make_numbers() de créer un tableau de cinq entiers.
4.2. Création du tableau
a = make_numbers(n);
Cette instruction appelle la fonction make_numbers() avec la valeur 5.
La fonction réalise une allocation dynamique de mémoire, remplit le tableau et retourne son adresse.
Le pointeur a reçoit donc l'adresse du tableau.
Une vérification est ensuite réalisée :
if (!a)
    return 1;
Cette condition permet de vérifier si la création du tableau a échoué.
Si a vaut NULL, le programme quitte avec un code de retour égal à 1.
5. Analyse de l'aliasing des pointeurs
5.1. Affectation du pointeur b
b = a;
Cette instruction copie la valeur du pointeur a dans le pointeur b.
Cela signifie que les deux pointeurs désignent désormais la même zone mémoire.
Ce phénomène est appelé Aliasing.
L'aliasing signifie que plusieurs variables ou pointeurs peuvent accéder à un même objet ou à une même zone mémoire.
Dans ce programme, a et b ne possèdent pas deux tableaux distincts. Ils partagent le même tableau.
5.2. Affichage des adresses et des valeurs
printf("  a=%p b=%p a[2]=%d b[2]=%d\n",
       (void *)a, (void *)b, a[2], b[2]);
Cette instruction affiche :
L'adresse contenue dans a.
L'adresse contenue dans b.
La valeur du troisième élément accessible par a.
La valeur du troisième élément accessible par b.
Avant la libération de la mémoire, les deux pointeurs sont valides et désignent le même tableau.
Les adresses affichées pour a et b sont donc identiques.
Les valeurs de a[2] et b[2] sont également identiques, car les deux pointeurs accèdent au même élément du tableau.
6. Analyse de la libération de mémoire
free(a);
Cette instruction libère la mémoire précédemment allouée par malloc().
Après cette opération, la zone mémoire n'est plus considérée comme appartenant au programme.
Cependant, la libération de la mémoire ne modifie pas automatiquement la valeur des autres pointeurs qui contiennent cette adresse.
Le pointeur b conserve donc une adresse correspondant à la zone mémoire qui vient d'être libérée.
Il devient alors un pointeur pendant (Dangling Pointer).
Un pointeur pendant est un pointeur qui conserve une adresse d'une zone mémoire dont la durée de vie ou la validité est terminée.
7. Analyse du Use-After-Free
7.1. Utilisation du pointeur après libération
printf("  after free(a): b=%p (dangling)\n", (void *)b);
Cette instruction affiche l'adresse contenue dans b.
L'affichage de l'adresse elle-même ne constitue pas une lecture du tableau libéré.
Cependant, le pointeur b est désormais un pointeur pendant, car la mémoire qu'il désignait a été libérée.
7.2. Lecture de la mémoire libérée
printf("  reading b[2]=%d\n", b[2]);
Cette instruction tente de lire le troisième élément du tableau à travers b.
Or, la mémoire associée à ce tableau a déjà été libérée par free(a).
Cette opération constitue une utilisation de mémoire après libération (Use-After-Free).
Le comportement est indéfini en C. La valeur affichée n'est pas garantie et le programme peut également se terminer anormalement.
7.3. Écriture dans la mémoire libérée
b[3] = 1234;
Cette instruction tente d'écrire une nouvelle valeur dans une zone mémoire qui a déjà été libérée.
Cette opération constitue également un comportement indéfini.
Le programme ne garantit pas que la mémoire reste disponible, ni qu'elle conserve les valeurs précédemment stockées.
Cette situation peut provoquer un crash, une corruption mémoire ou d'autres comportements imprévisibles.
8. Tableau récapitulatif du déroulement
Étape
Opération
Résultat
1
Initialisation de n
n = 5
2
Appel de make_numbers(5)
Allocation du tableau
3
Remplissage du tableau
0, 11, 22, 33, 44
4
Affectation b = a
Les deux pointeurs désignent le même tableau
5
Affichage initial
Les adresses sont identiques
6
free(a)
Le tableau est libéré
7
Utilisation de b
b devient un pointeur pendant
8
Lecture b[2]
Use-After-Free
9
Écriture b[3] = 1234
Utilisation de mémoire libérée

9. Intérêt pour la cybersécurité
L'étude de ce programme permet de comprendre plusieurs notions fondamentales en cybersécurité :
Aliasing : comprendre comment plusieurs pointeurs peuvent désigner la même zone mémoire.
Heap Memory : comprendre le fonctionnement de la mémoire dynamique.
free() : comprendre la libération de mémoire.
Dangling Pointer : identifier un pointeur qui conserve une adresse devenue invalide.
Use-After-Free : comprendre les conséquences d'une utilisation de mémoire après libération.
Gestion des pointeurs : apprendre à maintenir la validité des références mémoire.
Les vulnérabilités de type Use-After-Free peuvent avoir des conséquences importantes en cybersécurité.
Selon les circonstances, elles peuvent entraîner des crashs, des corruptions mémoire ou des risques d'exploitation. Leur impact dépend notamment du programme, de l'environnement d'exécution et des mécanismes de protection.
La gestion rigoureuse de la durée de vie des objets et des pointeurs est donc essentielle pour développer des applications sécurisées.
10. Détection avec Valgrind
Le programme mentionne Valgrind, un outil d'analyse mémoire qui permet notamment d'identifier certaines erreurs liées à la gestion de la mémoire.
Il peut être utilisé pour détecter des problèmes tels que les accès à des zones mémoire invalides, certaines utilisations après libération et les fuites mémoire.
Valgrind permet ainsi d'aider les développeurs à analyser le comportement d'un programme et à identifier des erreurs mémoire pendant son exécution.
11. Correction du programme
Le problème vient du fait que le pointeur b conserve une référence à la mémoire libérée par free(a).
Une approche plus sûre consiste à éviter toute utilisation des pointeurs après la libération de la mémoire.
Par exemple, après avoir libéré la mémoire, les pointeurs concernés peuvent être réinitialisés à NULL :
free(a);
a = NULL;
b = NULL;
Cette méthode permet d'éviter de conserver des pointeurs pendants dans ces variables.
Toutefois, réinitialiser uniquement a ne suffit pas, puisque b possède sa propre copie de l'adresse. Il faut donc gérer explicitement les autres pointeurs concernés.
La meilleure pratique consiste à définir clairement la responsabilité de la libération de la mémoire et à éviter de réutiliser un objet après sa libération.
12. Conclusion
Ce programme constitue un exemple pratique de manipulation des pointeurs et de gestion de la mémoire dynamique en langage C.
Il permet d'observer le phénomène d'aliasing, dans lequel deux pointeurs désignent une même zone mémoire, ainsi que les conséquences de la libération de cette zone mémoire.
Après l'appel à free(a), le pointeur b conserve une adresse devenue invalide pour l'utilisation de l'objet. Les opérations de lecture et d'écriture réalisées à travers ce pointeur illustrent une vulnérabilité de type Use-After-Free.
En conclusion, cet exercice souligne l'importance de maîtriser les pointeurs, de respecter la durée de vie des allocations et de sécuriser les opérations de libération mémoire.
Ces connaissances sont essentielles pour la programmation système et l'étude des vulnérabilités mémoire en cybersécurité.



