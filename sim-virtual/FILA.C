#include "FILA.H"
#include "LISTA.H"
#include <stdlib.h>
#include <stdio.h>

typedef struct FIL_tagFila {
	int capacidade;
	LIS_tppLista lista;
}FIL_tpFila;

FIL_tppFila FIL_criaFila (int capacidade, void( * ExcluirValor ) ( void * pDado ) )
{
	FIL_tppFila fila=(FIL_tpFila*)malloc(sizeof(FIL_tpFila));
	fila->capacidade=capacidade;
	LIS_CriarLista(&(fila->lista),ExcluirValor);
	return fila;
}

int FIL_insereElem (FIL_tppFila fila,void* pValor)
{
	if(fila->capacidade==LIS_ObtemNumElementos(fila->lista))
	{
		printf("\nFila cheia!");
		return 0;
	}
	LIS_IrFinalLista( fila->lista ) ;
	LIS_InserirElementoApos(fila->lista,pValor);
	return 1;	
}

void* FIL_retiraElem (FIL_tppFila fila)
{
	//assertiva de entrada: fila não está vazia!!!!!
	void* pValor;
	LIS_IrInicioLista(fila->lista);
	LIS_ObterValor( fila->lista , &pValor);
	LIS_ExcluirElemento(fila->lista);
	return pValor;
}

void FIL_apagaFila (FIL_tppFila fila)
{
	LIS_DestruirLista(fila->lista);
	free(fila);
	return;
}

int FIL_estaVazia (FIL_tppFila fila)
{
	if(LIS_ObtemNumElementos(fila->lista)==0)
	{
		return 1;
	}
	return 0;
}

int FIL_contemElem (FIL_tppFila fila, void* pValor, int (*compara) ( void*pValor1 , void*pValor2 ) )
{
	LIS_tpCondRet ret=LIS_BuscarElemento(fila->lista,pValor,compara);
	if(ret==LIS_CondRetFimLista||ret==LIS_CondRetListaVazia)
	{
		return 0;
	}
	return 1;
}

