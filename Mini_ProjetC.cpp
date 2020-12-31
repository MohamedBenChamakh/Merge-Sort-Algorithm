#include <stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>

char nf[100];

/* DEFINITION STRUCTURE */

typedef struct fiche
{
char nom[25],prenom[25];
float sal;
}fiche;



typedef enum{DansChute ,DansMonotonie ,FinDeFichier }TEtats ;


/* FONCTION PRELIMINAIRE */

void creer(char nf[100])
{
FILE *f=fopen(nf,"wb");
if(f==NULL)
	printf("\n probleme de creation du fichier!\n");
fclose(f);
}

void ajout(char nf[10])
{
fiche e;
FILE *f=fopen(nf,"ab");

printf("\nnom: ");fflush(stdin);
gets(e.nom); 
printf("prenom: "); fflush(stdin);
gets(e.prenom);
printf("salaire annuel: "); fflush(stdin);
scanf("%f",&e.sal);
fwrite(&e,sizeof(e),1,f);
fclose(f);
}


void affiche(char nf[100])
{
fiche e;
FILE *f=fopen(nf,"rb");
puts("***********LE CONTENU DU FICHIER***************");
while(!feof(f))
{
	fread(&e,sizeof(e),1,f);
	if(!feof(f))
		printf("%s\t%s\t%.3fDT\n",e.nom,e.prenom, e.sal);
}
fclose(f);
}


TEtats LireElements(FILE *Fp, fiche *PtrElem) 
{
	TEtats x;
	fiche PtrSuiv;
	int n;
	if(PtrElem==NULL)
	{
		n=fread(PtrElem,sizeof(fiche),1,Fp);
		x=DansMonotonie;
	}
	else
	{
		n=fread(&PtrSuiv,sizeof(fiche),1,Fp);
		if(n==0)
		{
			x=FinDeFichier;
			PtrElem=NULL;
		}
		else if(PtrElem->sal>PtrSuiv.sal)
		{
			x=DansChute;
			*PtrElem=PtrSuiv;
		}
		else if(PtrElem->sal<=PtrSuiv.sal)
		{
			x=DansMonotonie;
			*PtrElem=PtrSuiv;
		}
		
		
	}
	return x;
}

TEtats CopierElement (fiche  *PtrElem, FILE  *FileIn,FILE *FileOut) 
{
	TEtats x;
	fwrite(PtrElem,sizeof(fiche),1,FileOut);
	if(x!=FinDeFichier)
		x=LireElements(FileIn,PtrElem) ;
	

	return x;
}


TEtats CopierMonotonie (fiche *PtrElem, FILE *FileIn, FILE *FileOut) 
{
TEtats x;

x=CopierElement(PtrElem,FileIn,FileOut);
while(x==DansMonotonie)
	{
		x=CopierElement(PtrElem,FileIn,FileOut);		
	}
	
	return x;

}


/* FONCTION DU PROBLEME TRI */

void FusionnerFichiers( FILE *aux1, FILE *aux2, FILE *dest) 
{
	dest=fopen(nf,"wb");
	aux1=fopen("aux1.dat","rb");
	aux2=fopen("aux2.dat","rb");
	fiche PtrElem,PtrElem2;
	TEtats x1,x2;

	printf("\nFUSION EN COURS...");
	x1=LireElements(aux1,&PtrElem);
	x2=LireElements(aux2,&PtrElem2);
			
	while(x1!=FinDeFichier || x2!=FinDeFichier)
	
	{
		if(x1==FinDeFichier )

		{
			printf("\n\n**********Dans X2 (FinDeFichier x1) *************");
			x2=CopierMonotonie(&PtrElem2,aux2,dest);
		
		}
		else 
		{
		
		if(x2==FinDeFichier)
	
		{
			printf("\n\n**********Dans X1 (FinDeFichier x2)*************");

			x1=CopierMonotonie(&PtrElem,aux1,dest);
		
		}
		else if(x1==DansMonotonie || x2==DansMonotonie)
		{
			//ALGORITHME D INTERCLASSEMENT
			
			while(x1==DansMonotonie || x2==DansMonotonie)
			{
				if(x1!=DansMonotonie)
				{
					printf("\n\n**********Dans X2 (Pas Dans Monotonie x1)*************");
					x2=CopierMonotonie(&PtrElem2,aux2,dest);

	
				}
				else 
				{
				
				if(x2!=DansMonotonie)
				{
					printf("\n\n**********Dans X1 (Pas Dans Monotonie x2)*************");
					x1=CopierMonotonie(&PtrElem,aux1,dest);
		
				}
				else
				{
					if(PtrElem.sal<=PtrElem2.sal)
					{
						printf("\n\n**********Dans X1 *************");
						x1=CopierElement(&PtrElem,aux1,dest);
					
					}
					else
					{
						printf("\n\n**********Dans X2 *************");
						x2=CopierElement(&PtrElem2,aux2,dest);
		
					}
				}
				
				}
			}
		}
		
		
		}
	
			///////////////////////////////
		if(x1==DansChute)
			printf("\nx1=DansChute");
		else if(x1==DansMonotonie)
			printf("\nx1=DansMonotonie");
		else if(x1==FinDeFichier)
			printf("\nx1=FinDeFichier");
		if(x2==DansChute)
			printf("\nx2=DansChute");
		else if(x2==DansMonotonie)
			printf("\nx2=DansMonotonie");
		else if(x2==FinDeFichier)
			printf("\nx2=FinDeFichier");
	}
	


	fclose(dest);
	fclose(aux1);
	fclose(aux2);
}

/* NOMBRE DE PAS NECESSAIRE POUR TRIER LE FICHIER */
int NombrePas(FILE *Srce)
{
	fiche *PtrElem;
	TEtats x;
	int nb=1;
	while(x!=FinDeFichier)
	{
		printf("\n\nlecture d elements en cours...");
		x=LireElements(Srce,PtrElem) ;
		printf("\nle resultat de PtrElem=%.3f",PtrElem->sal);
		
		if(x==DansChute)
			printf("\nx=DansChute");
		else if(x==DansMonotonie)
			printf("\nx=DansMonotonie");
		else if(x==FinDeFichier)
			printf("\nx=FinDeFichier");
		
			
		if(x==DansChute )
			nb+=1;
		printf("\nnb=%d",nb);
		
	
	}
	
		
	fseek(Srce,0,SEEK_SET);
	return nb;
}


long  DistribuerFichiers( FILE *Srce, FILE *aux1, FILE *aux2) 
{
	Srce=fopen(nf,"rb");
	aux1=fopen("aux1.dat","wb");
	aux2=fopen("aux2.dat","wb");
	int i=0,nb;
	long NBMonotonies=1;
	TEtats x;
	fiche PtrElem;
	
	printf("\nrecherche du nombre de pas en cours...");
	nb=NombrePas(Srce);

	if(nb % 2 ==0)
		 nb=nb/2;
	else
		 nb=nb/2+1;

	printf("\n\nLe nombre de pas necessaire est : %d\n\n",nb);
	printf("\n\nDISTRIBUTION EN COURS... ");
	x=LireElements(Srce,&PtrElem);
	
	while(x==DansMonotonie)
	{
		x=CopierMonotonie(&PtrElem,Srce,aux1);
	
		if(x==DansChute)
			NBMonotonies++;
		
			
		
	}
	if(x!=FinDeFichier)
		x=CopierElement(&PtrElem,Srce,aux2);
	while(x!=FinDeFichier)
	{
		x=CopierMonotonie(&PtrElem,Srce,aux2);
		if(x==DansChute)
			NBMonotonies++;
	}
	
	fclose(Srce);
	fclose(aux1);
	fclose(aux2);

	return NBMonotonies;
	
}


void tri(FILE *Fp,FILE *Fpaux1,FILE *Fpaux2)
{
	
int NBMonotonies= DistribuerFichiers(Fp,Fpaux1,Fpaux2) ;
while(NBMonotonies>1)
{
	FusionnerFichiers(Fpaux1,Fpaux2,Fp) ; 
	NBMonotonies= DistribuerFichiers(Fp,Fpaux1,Fpaux2) ;
	printf("\n Le nombre de Monotonie est devenu : %d\n",NBMonotonies);
	printf("\n************Fpaux1************\n");
affiche("aux1.dat");
printf("\n************Fpaux2************\n");
affiche("aux2.dat");
	affiche(nf);

}

}


int main()
{

/* PRELIMINAIRE */

int n,i;

/* CHOISIR LE NOM DU FICHIER */

printf("\nsaisir le nom du fichier : ");
scanf("%s",nf);
strcat(nf,".bin");
///////////////////////////////

creer(nf);
printf("\ndonner le nombre de fiche:");
do 
	scanf("%d",&n); 
while(n<1);

for(i=1;i<n+1;i++)
{
	printf("\nMEMBRE NUM %d",i);
	ajout(nf);
}
	
	
affiche(nf);



/* PROBLEME  DE FUSION */

FILE *Fp ;
FILE *Fpaux1 ;
FILE *Fpaux2 ;
long NBMonotonies ; 


TEtats   Etat_A ;
TEtats   Etat_B ;

/* TESTE (3EME QUESTION) */
printf("\n************TESTE APRES DISTRIBUTION************\n");


NBMonotonies=DistribuerFichiers(Fp,Fpaux1,Fpaux2);
if(NBMonotonies==0)
	printf("\nle fichier est VIDE !");
else if(NBMonotonies==1)
	printf("\nle fichier est TRIE !");
else
	printf("\nle fichier N'EST PAS ENCORE TRIE !");

printf("\nle nombre de Monotonie est %ld",NBMonotonies);


/*AFFICHAGE DU RESULTAT */

printf("\n************Fpaux1************\n");
affiche("aux1.dat");
printf("\n************Fpaux2************\n");
affiche("aux2.dat");



////////////////////////////
printf("\n\n\n");
//////////////////////////


/* TESTE (5EME QUESTION) */

if(NBMonotonies >1)
{
	
printf("\n************TESTE APRES FUSION************\n");
FusionnerFichiers(Fpaux1,Fpaux2,Fp) ; 
}
else
	printf("\nLE FICHIER EST TRIE ");
printf("\n\n************FICHIER OBTENU************\n");
if(NBMonotonies>1)
affiche(nf);
printf("\n************Fpaux1************\n");
affiche("aux1.dat");
printf("\n************Fpaux2************\n");
affiche("aux2.dat");
printf("\nFIN DU FICHIER \n");

//////////////////////////


/* TESTE (7EME QUESTION) */

printf("\n************TESTE APRES TRI FUSION************\n");
printf("\nLe nombre de monotonie est %d ",NBMonotonies);
if(NBMonotonies!=1)
{
	tri(Fp,Fpaux1,Fpaux2);
printf("\n************RESULTAT************\n");
affiche(nf);
}




//////////////////////////



/* EXTENSION DU PROGRAMME */





/////////////////////////// 
return 0;
}

