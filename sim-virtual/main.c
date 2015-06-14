#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"LISTA.H"
#include"FILA.H"
#define TRUE 1
#define FALSE 0

typedef struct quadro_fisico
{
    int R;
    int M;
    unsigned int endereco; 
    int time;

}Quadro_fisico;

int encontraValorShift(int bytes)
{
	int s=0;
	while((bytes/=2)>0)
		s++;
	return s+10;
}

int compara1(void *pValor1, void* pValor2)
{
	unsigned int bla;
	Quadro_fisico * quadro1,*quadro2;
	quadro1=(Quadro_fisico*)pValor1;
	quadro2=(Quadro_fisico*)pValor2;
	bla=quadro1->endereco;
	if( (quadro1->endereco)==(quadro2->endereco) )
	{
		return 0;
	}

	return 1;

}

int compara2(void *pValor1, void* pValor2)
{
	Quadro_fisico * quadro1=(Quadro_fisico*)pValor1;

	if(quadro1->M==0)
		return 0;

	return 1;

}

void trata_NRU(FILE * fonte, FILE * saida , int num_max , int s, int debug)
{
	LIS_tppLista pLista;
	Quadro_fisico *quadro, *quadro_lis;
	int time=0,n=0,pf=0,rd=0;
	char rw;
	LIS_CriarLista(&pLista,free);
	quadro=(Quadro_fisico*)malloc(sizeof(Quadro_fisico));
	while(fscanf(fonte, "%x %c ", &quadro->endereco, &rw)==2)
	{
		(quadro->endereco)>>=s;
		quadro->time=time;
		quadro->R=TRUE;

		if(rw=='W')
			quadro->M=TRUE;
		else
			quadro->M=FALSE;

		//buscar

		if(LIS_BuscarElemento(pLista , (void*)quadro, compara1)==LIS_CondRetOK)//encontrou
		{

			LIS_AlterarValor(pLista,(void*)quadro);

		}
		else //nao encontrou
		{
			if(n<num_max)//há espaço na lista
			{
				n++;
				LIS_IrInicioLista(pLista);
				LIS_InserirElementoAntes(pLista,(void*)quadro);
			}
			else //page fault
			{
				pf++;
				if(LIS_BuscarElemento(pLista , NULL, compara2)==LIS_CondRetOK)//existe elemento nao modificado
				{
					LIS_ObterValor(pLista,(void**)&quadro_lis);
					if(debug==TRUE)
					{
						fprintf(saida,"Page %u substituida em t=%d\n",quadro_lis->endereco,time);
					}
					LIS_AlterarValor(pLista,(void*)quadro);
				}
				else// todos foram modificados
				{
					rd++;
					LIS_IrFinalLista(pLista);

					LIS_ObterValor(pLista,(void**)&quadro_lis);
					if(debug==TRUE)
					{
						fprintf(saida,"Page %u reescrita em t=%d\n",quadro_lis->endereco,time);//mensagem log
					}

					LIS_AlterarValor(pLista,(void*)quadro);
				}
			}
		}

		time++;
		quadro=(Quadro_fisico*)malloc(sizeof(Quadro_fisico));
	}
	fprintf(saida,"\nNumero de page faults: %d\nPaginas escritas: %d",pf,rd);
}

void trata_LRU(FILE * fonte, FILE * saida , int num_max , int s, int debug)
{
	LIS_tppLista pLista;
	Quadro_fisico *quadro, *quadro_lis;
	int rw,time=0,n=0,pf=0,rd=0;

	LIS_CriarLista(&pLista,free);
	quadro=(Quadro_fisico*)malloc(sizeof(Quadro_fisico));
	fprintf(saida,"LRU\n");
	while(fscanf(fonte, "%x %c ", &quadro->endereco, &rw)==2)
	{
		quadro->endereco>>=s;
		quadro->time=time;
		quadro->R=TRUE;

		if(rw=='W')
			quadro->M=TRUE;
		else
			quadro->M=FALSE;

		//buscar

		if(LIS_BuscarElemento(pLista , (void*)quadro, compara1)==LIS_CondRetOK)//encontrou
		{
			LIS_ExcluirElemento(pLista);

			LIS_IrInicioLista(pLista);
			LIS_InserirElementoAntes(pLista,(void*)quadro);

		}
		else //nao encontrou
		{
			if(n<num_max)//há espaço na lista
			{
				n++;
				LIS_IrInicioLista(pLista);
				LIS_InserirElementoAntes(pLista,(void*)quadro);
			}
			else //page fault
			{
				pf++;

				LIS_IrFinalLista(pLista);

				LIS_ObterValor(pLista,(void**)&quadro_lis);

				if(quadro_lis->M==TRUE)
				{
					if(debug==TRUE)
					{
						fprintf(saida,"Page %u reescrita em t=%d\n",quadro_lis->endereco,time);//mensagem log
					}
					rd++;
				}
				else
				{
					if(debug==TRUE)
					{
						fprintf(saida,"Page %u substituida em t=%d\n",quadro_lis->endereco,time);
					}
				}
				LIS_ExcluirElemento(pLista);

				LIS_IrInicioLista(pLista);
				LIS_InserirElementoAntes(pLista,(void*)quadro);
			}
		}

		time++;
		quadro=(Quadro_fisico*)malloc(sizeof(Quadro_fisico));
	}
	fprintf(saida,"\nNumero de page faults: %d\nPaginas escritas: %d",pf,rd);

}

void trata_SEG(FILE * fonte, FILE * saida , int num_max , int s , int debug)
{
	FIL_tppFila pFila = FIL_criaFila(num_max,NULL);

	Quadro_fisico *quadro, *quadro_lis;
	int rw,time=0,n=0,i,rd=0,pf=0;
	quadro=(Quadro_fisico*)malloc(sizeof(Quadro_fisico));
	
	while(fscanf(fonte, "%x %c ", &quadro->endereco, &rw)==2)
	{
		quadro->endereco>>=s;
		quadro->time=time;
		quadro->R=TRUE;

		if(rw=='W')
			quadro->M=TRUE;
		else
			quadro->M=FALSE;

		//buscar

		if(FIL_contemElem(pFila , (void*)quadro, compara1)==TRUE)//encontrou
		{
			FIL_retiraElem(pFila);
			FIL_insereElem(pFila,(void*)quadro);

		}
		else //nao encontrou
		{
			if(n<num_max)//há espaço na lista
			{
				n++;
				FIL_insereElem(pFila,(void*)quadro);
			}
			else //page fault
			{

				pf++;
				quadro_lis=(Quadro_fisico*)FIL_retiraElem(pFila);
			
				while(quadro_lis->R==TRUE)//merece segunda chance
				{
					
					quadro_lis->R=FALSE;
					
					FIL_insereElem(pFila,(void*)quadro_lis);
					quadro_lis=(Quadro_fisico*)FIL_retiraElem(pFila);
					
				}//fim merece segunda chance

				if(quadro_lis->M==TRUE)
				{
					if(debug==TRUE)
					{
						fprintf(saida,"Page %u reescrita em t=%d\n",quadro_lis->endereco,time);//mensagem log
					}
					rd++;
				}
				else
				{
					if(debug==TRUE)
					{
						fprintf(saida,"Page %u substituida em t=%d\n",quadro_lis->endereco,time);
					}
				}
				FIL_insereElem(pFila,(void*)quadro);
			}
		}

		time++;
		quadro=(Quadro_fisico*)malloc(sizeof(Quadro_fisico));
		if((time%10)==9) //zera todo mundo
		{
			for(i=0;i<n;i++)
			{
				quadro_lis=(Quadro_fisico*)FIL_retiraElem(pFila);
				quadro_lis->R=FALSE;
				FIL_insereElem(pFila,(void*)quadro_lis);
			}
		}//fim zera todo mundo
	}
	fprintf(saida,"\nNumero de page faults: %d\nPaginas escritas: %d",pf,rd);
}

int main(int argc, char *argv[])
{
    int num_max, ocupados=0,modo_depuracao=0;
    int tam_pag=atoi(argv[3]), tam_mem=atoi(argv[4]);
    FILE *saida,* fonte = fopen(argv[2],"r");
	saida = fopen("log.txt","w");
	fprintf(saida,"INF1019 - T2\nAlunos: Clara Szwarcman e Guilherme Simas\nRelatorio do simulador de memória virtual\nParametros utilizados na simulacao: Algoritmo de substituicao-%s | Arquivo de entrada-%s | Tamanho do quadro de pagina-%dKB | Tamanho de memoria fisica disponivel-%dKB\n",argv[1],argv[2],atoi(argv[3]),atoi(argv[4]));
	if(strcmp(argv[4],"-D")==0)
	{
		modo_depuracao=TRUE;
		fprintf(saida,"----------SIMULADOR EM MODO DEPURACAO----------\n");
	}
    if(fonte==NULL)
    {
        printf("Arquivo nao encontrado\n");
        exit(1);
    }

    num_max=tam_mem/tam_pag;

    if(strcmp("NRU", argv[1])==0)
        trata_NRU(fonte,saida,num_max, encontraValorShift ( tam_pag ) , modo_depuracao) ;
    else if(strcmp("LRU", argv[1])==0)
        trata_LRU(fonte,saida,num_max, encontraValorShift ( tam_pag ) ,modo_depuracao) ;
    else if(strcmp("SEG", argv[1])==0)
        trata_SEG(fonte,saida,num_max, encontraValorShift ( tam_pag ) ,modo_depuracao) ;

	fprintf(saida,"\n============fim do log============");

    fclose(fonte);
	fclose(saida);

    return 0;
}
