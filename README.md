# Merge-Sort-Algorithm

Mini Projet : Tri d’un fichier de grande taille

Présentation générale
Le développement d'un projet est un moyen de progresser dans l'apprentissage d'un langage de programmation, c'est dans cet esprit qu'il vous est proposé.
Il doit vous permettre de consolider les connaissances acquises en TP et d’en acquérir de nouvelles. 
Pour cela, vous devrez développer, un programme qui permet de trier un fichier de grande taille selon le principe expliqué ci-dessous.
Ce travail doit être fait en binôme et la période qui vous sera accordée est de deux semaines à compter du Mercredi 15/01/2020.
I.	Le problème du tri de fichiers de grande taille
Remarques préliminaires :
Nous dirons qu’un fichier est de « grande taille », s’il est impossible de stocker son contenu totalement en mémoire centrale afin d’appliquer une méthode de tri en mémoire comme :
•	Tri rapide  (quick sort)
•	Tri par tas (heap sort)
•	Tri shell etc…

Les données du problème :
Un fichier séquentiel constitué d’éléments pouvant être comparés.
Résultat :
Un fichier contenant les mêmes éléments classés par ordre croissant.	

Quelques définitions :
Une monotonie est une suite non décroissante (il peut y avoir des éléments de «même valeur»), de longueur maximale d’éléments contigus (consécutifs) dans un fichier donné.

Une chute est une paire d’éléments contigus dont le second est « inferieur » au premier.
Quelques propriétés :
•	Un fichier vide contient 0 (zéro) monotonie.
•	Un fichier trié (non vide) ne contient qu’une seule monotonie.
•	Une monotonie se termine soit au milieu d’une chute soit en fin de fichier.

II.	Le principe du tri fusion :
Cas particulier d’un fichier contenant 2 monotonies.
Le tri consiste alors à distribuer chaque monotonie sur un fichier différent (ceux-ci ne contiendront alors qu’une seule monotonie : ils sont donc ordonnés), puis à fusionner ces fichiers (par interclassement des éléments de chaque monotonie).
Cas général
Il faut d’abord fixer le nombre de fichiers auxiliaires utilisés (nous prendrons 2 fichiers auxiliaires).
La distribution des monotonies se fera alternativement sur chaque fichier. Dans chaque fichier le nombre de monotonies est réduit de moitié par rapport au nombre initial (+1 dans le cas d’un nombre initial de monotonies impair).
En résumé 
Le tri fusion est un processus itératif composé :
•	D’une phase de distribution des données sur deux fichiers (par copie alternative de monotonies sur l’un ou l’autre des fichiers auxiliaires).
•	D’une phase de fusion des fichiers auxiliaires sur un troisième par interclassement.
Exercices
Déterminer le nombre de pas d’itération nécessaires pour trier un fichier contenant initialement seize monotonies.
Même problème pour un fichier contenant neuf monotonies.

III.	Analyse :

ANALYSE INFORMATIQUE DU PROBLEME DU TRI

Les données :

FILE *Fp ;		//pointeur sur le fichier à trier
FILE *Fpaux1 ;		//pointeur sur le 1er fichier auxiliaire
FILE *Fpaux2 ;		//pointeur sur le 2ème fichier auxiliaire

long NBMonotonies ; 	//pour le calcul du nombre de monotonies

Les fonctions :
 void   FusionnerFichiers( FILE *aux1, FILE *aux2, FILE *dest) ;
long   DistribuerFichiers( FILE *Srce, FILE *aux1, FILE *aux2) ;

L’algorithme (de principe) :





Mise au point :
Prévoir dès la phase de conception, les moyens de tester les éléments essentiels du programme.
Par exemple
•	Créer un fichier test de quelques enregistrements
•	Prévoir une fonction permettant l’affichage d’un fichier
•	Afficher le nombre de monotonies, etc. ...

LE PROBLEME DE LA FUSION
Données :
Deux fichiers (a et b) contenant un nombre quelconque d’éléments.
Résultat :
Un fichier (c) contenant l’ensemble des éléments des deux fichiers précédents.
Pour chaque paire de monotonies prise simultanément sur chaque fichier, une monotonie doit être formée par interclassement.
Tous les éléments des fichiers de départ (a et b) doivent être transférés sur le fichier c. dans le cas d’éléments de « même valeur », un choix de priorité arbitraire est effectué.

Algorithme de l’interclassement de deux monotonies

TQ ( DansMonotonie sur  a OU DansMonotonie sur b)
SI (PAS DansMonotonie sur a)
CopierMonotonie de b vers c
SINON
SI  (PAS DansMonotonie sur b)
CopierMonotonie de a vers c
SINON /*DansMonotonie sur a et b */
SI (Element courant de a<= Elemnt courant b)
CopierMonotonie de a vers c
SINON
Copierelement de b vers c

Algorithme général
TQ ( Pas FinDeFichier   sur a OU Pas FinDeFichier sur b)
Si (FinDeFichier sur a)
CopierMonotonie de b vers c
SINON
SI (FinDeFichier sur b)
CopierMonotonie de a vers c
SINON /*interclassement de deux monotonies*/
...	/* cf. algorithme précedent */
Analyse informatique : les données
Les algorithmes précédents mettent en évidence le besoin de savoir à tout instant dans quel état se trouvent les fichiers a et b.
De plus, chaque opération de lecture sur un fichier permet de récupérer en mémoire un enregistrement qui sera par la suite comparé à un élément de l’autre fichier, puis recopié sur le fichier de sortie. Il est donc nécessaire de faire apparaître dans la fonction fusionner, des variables qui représenteront les éléments courant de chaque fichier d’entrée.
Typedef enum {DansChute, DansMonitonie, FinDeFichier} TEtats ;
TEtats   Etat_A ;		// Etat sur le fichier A
TEtats   Etat_B ;		// Etat sur le fichier B
Telements    Elem_A ;	//Elément courant issu du fichier A

Telements    Elem_B;        //Elément  courant issu du fichier B
Analyse informatique : les prototypes de fonction
TEtats   LireElements(FILE *Fp, TElements *PtrElem) ;
Cette fonction sera appelée, en particulier, au début des procédures de fusion et de distribution afin de :
 	Récupérer le premier élément d’un fichier s’il existe (celui-ci sera rangé à l’adresse PtrElem)
 	Et de retourner l’état du fichier (DansChute, DansMonitonie ou FinDeFichier)
TEtats CopierElement (TElements  *PtrElem, FILE  *FileIn,FILE *FileOut) ;
Cette fonction permet de recopier l’élément courant (dont l’adresse est rangée dans PtrElem) du fichier FileIn sur le fichier FileOut, puis effectue la lecture (cf. fonction précédente) de l’élément suivant sur FileIn. Ce nouvel élément est rangé à l’adresse passée en paramètre (PtrElem). Elle retourne le nouvel état du fichier FileIn ((DansChute, DansMonitonie ou FinDeFichier)
TEtats CopierMonotonie (TElements *PtrElem, FILE *FileIn, FILE *FileOut) ;
Cette fonction effectue la copie de l’élément courant rangé à l’adresse PtrElem et de tous les éléments suivants de la monotonie en cours, du fichier FileIn sur le fichier FileOut.
En fin de copie, la fonction retourne le nouvel état du fichier FileIn, et a rangé à l’adresse PtrElem le dernier élément lu sur FileIn si la fin de ce fichier n’a pas été atteinte.

NOTE : cette fonction utilise la fonction CopierElement.

LE PROBLEME DE LA DISTRIBUTION
Cette fonction effectue la copie alternativement sur le fichier auxiliaire a ou le fichier auxiliaire b, des monotonies contenues dans le fichier initial c. elle retourne le nombre total de monotonies qui ont été transférées sur les deux fichiers auxiliaires.

Il faut pouvoir dans cette fonction détecter la fin d’une monotonie (soit au milieu d’une chute, soit en fin de fichier).

Les fonctions décrites précédemment peuvent être utilisées.

IV.	TRAVAIL A EFFECTUER
STRUCTURE DU FICHIER A TRIER
Le fichier à trier contient les enregistrements constitués de :

•	Un nom (chaine de 25 caractères)
•	Un prénom (chaine de 25 caractères)
•	Un salaire annuel (réel exprimé en DT)

On souhaite obtenir un fichier ordonné par salaire annuel croissant.



TRAVAIL PRELIMINAIRE (1er PROGRAMME)
Réaliser les opérations suivantes :
•	Saisir une « fiche » (nom, prénom et salaire annuel)
•	Enregistrer une fiche dans un fichier
•	Afficher le contenu d’un fichier
•	Tester les fonctions précédentes
LE PROGRAMME DE TRI FUSION
Réaliser les opérations suivantes :
1.	Ecrire les fonctions décrites dans l’analyse du problème de la fusion
2.	Compléter l’analyse informatique de la phase de distribution, et de réaliser cette fonction
3.	Tester cette fonction
•	Utiliser le fichier crée précédemment
•	Afficher le nombre de monotonies de ce fichier
•	Afficher le contenu des deux fichiers auxiliaires obtenus après la phase de distribution
4.	Réaliser la fonction de fusion
5.	Tester une fonction
•	Utiliser les deux fichiers crée précédemment
•	Fusionner ces deux fichiers dans un troisième
•	Afficher le contenu du fichier obtenu
6.	Réaliser la fonction de tri fusion d’un fichier
7.	Tester cette fonction
•	Avec le fichier créé dans la phase préliminaire
•	Avec le même fichier déjà ordonné
•	Avec un fichier de plus grande taille (afficher le nombre de monotonies obtenues après chaque distribution, et éventuellement le contenu du fichier obtenu après chaque fusion)

EXTENSION DU PROGRAMME
On souhaite pouvoir trier ce fichier par ordre alphabétique de leur nom ET prénom. Il peut en effet avoir dans le même fichier plusieurs personnes ayant le même nom de famille (on fera l’hypothèse qu’ils ne peuvent avoir le même prénom).
