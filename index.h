#include <iostream>
#include <string.h>
#define TAM 20

struct Elem
{
	char nome[20];
	int nr;
};
struct Lista
{
	Elem M[TAM];
	int Fim;
};

void Lins(Lista *L, Elem X)
{
	int i=L->Fim;
	if (i<TAM)
	{
		while ((i>0)&&(strcmp(X.nome,L->M[i-1].nome)<0))
		{
			strcpy(L->M[i].nome,L->M[i-1].nome);
			L->M[i].nr=L->M[i-1].nr;
			i--;
		}
		strcpy(L->M[i].nome,X.nome);
		L->M[i].nr=X.nr;
		L->Fim++;
	}
}

char Lrem(Lista *L,Elem X)
{
	int I=0;
	while ((I<L->Fim) && (strcmp(X.nome,L->M[I].nome)>0))//procurando a posição I do elemento
	    I++;
	if ((I<L->Fim) && (strcmp(X.nome,L->M[I].nome)==0))
	   { //removendo o elemento
	      while(I<L->Fim-1)
		  { 
		     strcpy(L->M[I].nome,L->M[I+1].nome);
		     L->M[I].nr=L->M[I+1].nr;
		     I++;
		  } 
		 L->Fim--;
		 return 1;	  
	   }
	return 0;
}

int procuranr(Lista *L, Elem X)
{
    int I=0;
	while ((I<L->Fim) && (strcmp(X.nome,L->M[I].nome)>0))//procurando a posição I do elemento
	    I++;	
   if ((I<L->Fim) && (strcmp(X.nome,L->M[I].nome)==0))
       return L->M[I].nr;
    else
       return -1;//não existe!!!!
}
/*
void mostralista(Lista *L)
{
	putchar('[');
	for(int I=0;I<L->Fim;I++)
	{
		printf("%s",L->M[I]);
		if (I<(L->Fim-1))
		   printf(",");
	}
	putchar(']');
}
*/

