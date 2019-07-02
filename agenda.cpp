#include <iostream>
#include <string.h>
#include "index.h"

struct reg
{
	char nome[20];
	char tel[10];
	char email[20];
};

int tamanho(FILE *);
void cadastrar(FILE *,Lista *);
void consultar(FILE *);
void geralista(FILE *,Lista *);
void consultanome(FILE *arq,Lista *L);
void geraarqtxt(FILE *);
void geraarqintervalo(FILE *,Lista *L);

main()
{
    int op;
    FILE *arq;
    Lista L;
    if ((arq=fopen("dados.dat","rb+"))==NULL)
       {
       	if ((arq=fopen("dados.dat","wb+"))==NULL)
       	{
       	  printf("Falha ao abrir o arquivo!\n");
		  system("pause");	 	
		}
	   }
	   
    geralista(arq,&L); //inicializa a lista L com os nomes 
                       //existentes no arquivo dados.dat
	do
	{
		system("CLS");
		printf("========== Agenda ==========\n");
		printf("1.Cadastrar\n");
		printf("2.Consultar por codigo\n");
		printf("3.Consulta por nome\n");
		printf("4.Gerar arquivo\n");
		printf("5.Gerar arquivo por intevalo\n");
		printf("6.Sair\n");
		printf("=================Contatos:%d=\n",tamanho(arq));
		printf("Opcao:");
		scanf("%d",&op);
		switch (op)
		{
			case 1://cadastrar novo contato
			       cadastrar(arq,&L);
			       break;
			case 2://consultar por código
			       consultar(arq);
				   break;
			case 3:consultanome(arq,&L);
			       break;
		    case 4: geraarqtxt(arq);
			       //gerar arquivo texto com todos os contatos 
		          //ordenados alfabeticamente
		           break;
		    case 5:geraarqintervalo(arq,&L);
				   //gerar arquivo texto por intervalo de nomes
		           break;
	    }
	} while (op!=6);
}

void geraarqintervalo(FILE *arq, Lista *L)
{
	char nomearq[20],com[20],fim[20];
	fflush(stdin);
	printf("Inicio do intervalo:");
	scanf("%c",&com);
	fflush(stdin);
	printf("Final do intervalo:");
	scanf("%c",&fim);
	fflush(stdin);
	printf("Nome do arquivo texto:");
	scanf("%s",nomearq);
	strcat(nomearq,".txt");
	FILE *arqtxt=fopen(nomearq,"w");
	if (!arqtxt)
	{
		printf("Nao foi possivel criar esse arquivo!\n");
		system("pause");
		return;
	}
	fprintf(arqtxt,"Nome                Telefone  E-mail\n");
	fprintf(arqtxt,"===============================================\n");
	int i=0;
	while((i<L->Fim) && (strcmp(L->M[i].nome,com)<0))
	{
		i++;
	}
	reg contato;
	while((i<L->Fim) && ((strcmp(L->M[i].nome,fim)<0) || (strcmp(L->M[i].nome,fim)==0)))
	{
		fseek(arq,sizeof(reg)*L->M[i].nr,SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		fprintf(arqtxt,"%-20s%-10s%-20s\n",contato.nome,contato.tel,contato.email);
		i++;
	}
	fprintf(arqtxt,"===============================================\n");
	fclose(arqtxt);
}

void geraarqtxt(FILE *arq)
{
	char nomearq[20];
	printf("Nome do arquivo texto:");
	scanf("%s",nomearq);
	strcat(nomearq,".txt");
	FILE *arqtxt=fopen(nomearq,"w");
	if (!arqtxt)
	{
		printf("Nao foi possivel criar esse arquivo!\n");
		system("pause");
		return;
	}
	fprintf(arqtxt,"Nome                Telefone  E-mail\n");
	fprintf(arqtxt,"===============================================\n");
	int nr;
	reg contato;
	for (nr=0;nr<tamanho(arq);nr++)
	{
        fseek(arq,nr*sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		fprintf(arqtxt,"%-20s%-10s%-20s\n",contato.nome,contato.tel,contato.email);
	}
	fprintf(arqtxt,"===============================================\n");
	fclose(arqtxt);
}

void consultanome(FILE *arq,Lista *L)
{
	reg contato;
	Elem X;
	fflush(stdin);
	printf("\nConsulta pelo nome\n");
	printf("\nInforme o nome...:");
	gets(X.nome);
	X.nr=procuranr(L,X);
	if ( X.nr!=-1)
	{
		fseek(arq,X.nr*sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		printf("\nNome......:%s",contato.nome);
		printf("\nTelefone..:%s",contato.tel);
		printf("\ne-mail....:%s\n",contato.email);
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}

void consultar(FILE *arq)
{
	reg contato;
	int nr;
	printf("\nConsulta pelo codigo\n");
	printf("\nInforme o Codigo...:");
	scanf("%d",&nr);
	if ( (nr<=tamanho(arq)) && (nr>0) )
	{
		fseek(arq,(nr-1)*sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		printf("\nNome......:%s",contato.nome);
		printf("\nTelefone..:%s",contato.tel);
		printf("\ne-mail....:%s\n",contato.email);
	}
	else
	{
		printf("\nNumero de registro invalido!\n");
	}
	system("pause");
}

void cadastrar(FILE *arq, Lista *L)
{
	reg contato;
	char confirma;
	fflush(stdin);
	printf("Cadastrando novo registro:\n");
	printf("\nNumero do registro:%d\n",tamanho(arq)+1);
	printf("Nome..........:");
	gets(contato.nome);
	printf("Telefone......:");
	gets(contato.tel);
	printf("e-mail........:");
	gets(contato.email);
	printf("\nConfirma <s/n>:");
	fflush(stdin);
	scanf("%c",&confirma);
	if (toupper(confirma)=='S')
	{
		printf("\n gravando...\n");
		fseek(arq,0,SEEK_END);
		fwrite(&contato,sizeof(reg),1,arq);
		Elem X;
		strcpy(X.nome,contato.nome);
		X.nr=tamanho(arq)-1;
		Lins(L,X);
	}
	system("pause");
}

int tamanho(FILE *arq)
{
	fseek(arq,0,SEEK_END);
	return ftell(arq)/sizeof(reg);
}

void geralista(FILE *arq,Lista *L)
{
	L->Fim=0;
	int nr;
	reg contato;
	Elem X;
	for (nr=0;nr<tamanho(arq);nr++)
	{
		fseek(arq,nr*sizeof(reg),SEEK_SET);
		fread(&contato,sizeof(reg),1,arq);
		strcpy(X.nome,contato.nome);
		X.nr=nr;
		Lins(L,X);	    
	}
	
}





