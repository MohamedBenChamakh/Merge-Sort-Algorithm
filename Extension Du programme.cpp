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
/*
int verif(char ch)
{
	FILE *Fp=fopen(nf,"rb");
	fiche *elem;
	char *x=elem->prenom;

	while(!feof(Fp))
	{
		fread(elem,sizeof(fiche),1,Fp);
		if(strcmp(ch,x)==0)
			return 0;
	
		}	
	close(Fp);
	return 1;

}*/
int verif(char p[50],char n[50],char nf[10])
{int v=0,x,i=1;
fiche s;
FILE *g=fopen(nf,"rb");
x=fread(&s,sizeof(s),1,g);

	while (x!=0)
	{
		if (strcmp(s.prenom,p)==0 && strcmp(s.nom,n)==0)
		     {printf("vous avez 2 Elements Egaux\n");
			   return 1 ;
		       }
		if(strcmp(s.prenom,"")==0 || strcmp(s.nom,"")==0)
		{printf("vous avez des champs vides\n");
			   return 1 ;
		       }
		printf("\n%s %s\n",s.nom,s.prenom);
		x=fread(&s,sizeof(s),1,g);

	}
fclose(g);
	
	return 0;
}
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
do
{
printf("prenom: "); fflush(stdin);
gets(e.prenom);
}while(verif(e.prenom,e.nom,nf));
printf("salaire annuel: "); fflush(stdin);
scanf("%f",&e.sal);
fwrite(&e,sizeof(e),1,f);
fclose(f);
}


void affiche(char nf[100])
{
fiche e;
int x=1;
FILE *f=fopen(nf,"rb");
puts("***********LE CONTENU DU FICHIER***************");
while(!feof(f) && x!=0)
{
	x=fread(&e,sizeof(fiche),1,f);
	if(x!=0)
		printf("%s\t%s\t%.3fDT\n",e.nom,e.prenom, e.sal);
}
fclose(f);
}


/* SECTEUR EXTENSION DU PROGRAMME */


/*
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
		else if(PtrElem->nom[0]>PtrSuiv.nom[0])
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
*/
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
		else if(strncmp(PtrElem->nom,PtrSuiv.nom,1)==0)
		{
			if(strncmp(PtrElem->prenom,PtrSuiv.prenom,1)>=0)
		     {
				x=DansChute;
			   *PtrElem=PtrSuiv;}
		
			else if(strncmp(PtrElem->prenom,PtrSuiv.prenom,1)<0)
			{
			x=DansMonotonie;
			*PtrElem=PtrSuiv;
			}
		}
		else if(strncmp(PtrElem->nom,PtrSuiv.nom,1)!=0)
		{
			if(strncmp(PtrElem->nom,PtrSuiv.nom,1)>0)
			{
				x=DansChute;
				*PtrElem=PtrSuiv;
			}
			else if(strncmp(PtrElem->nom,PtrSuiv.nom,1)<=0)
			{
					x=DansMonotonie;
					*PtrElem=PtrSuiv;
			}
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
/*
void FusionnerFichiers_alpha( FILE *aux1, FILE *aux2, FILE *dest) 
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
					if(PtrElem.nom[0]<=PtrElem2.nom[0])
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
*/

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
		else 
		{
			//ALGORITHME D INTERCLASSEMENT
			
			while(x1==DansMonotonie || x2==DansMonotonie)
			{
				printf("\nici");
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
					
				if(strcmp(PtrElem.nom,PtrElem2.nom)!=0)
				{
					if(strcmp(PtrElem.nom,PtrElem2.nom)<0)
					{
						printf("\n\n**********Dans X1 *************");
						x1=CopierElement(&PtrElem,aux1,dest);
					}
					else if(strcmp(PtrElem.nom,PtrElem2.nom)>0)
					{
					printf("\n\n**********Dans X2 *************");
					x2=CopierElement(&PtrElem2,aux2,dest);
					}
				}
				else if(strcmp(PtrElem.nom,PtrElem2.nom)==0)
				{
					if(strcmp(PtrElem.prenom,PtrElem2.prenom)<=0)
					{
						printf("\n\n**********Dans X1 *************");
						x1=CopierElement(&PtrElem,aux1,dest);
		    		 }
					else if(strcmp(PtrElem.prenom,PtrElem2.prenom)>0)
					{
						printf("\n\n**********Dans X2 *************");
						x2=CopierElement(&PtrElem2,aux2,dest);
					}
				}
				
				
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
	
	


	fclose(dest);
	fclose(aux1);
	fclose(aux2);
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
while(n<2);
FILE *f=fopen(nf,"wb");
for(int i=0;i<n;i++)
	ajout(nf);	
fclose(f);
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
printf("\n\n************FICHIER OBTENU************\n");
printf("\n************Fpaux1************\n");
affiche("aux1.dat");
printf("\n************Fpaux2************\n");
affiche("aux2.dat");
printf("\nFIN DU FICHIER \n");
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

/* EXTENSION DU PROGRAMME */
printf("\n*******EXTENSION DU PROGRAMME*********\n");
printf("\n************TESTE APRES TRI FUSION(PAR ORDRE ALPHABETIQUE)************\n");
if(NBMonotonies>1)
{
tri(Fp,Fpaux1,Fpaux2);
printf("\n************RESULTAT************\n");
affiche(nf);
}
/////////////////////////// 


return 0;
}
