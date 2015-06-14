typedef struct FIL_tagFila* FIL_tppFila;

FIL_tppFila FIL_criaFila (int capacidade, void ( * ExcluirValor ) ( void * pDado ) );

int FIL_insereElem (FIL_tppFila fila,void* pValor);

void* FIL_retiraElem (FIL_tppFila fila);

void FIL_apagaFila (FIL_tppFila fila);

int FIL_estaVazia (FIL_tppFila fila);

int FIL_contemElem (FIL_tppFila fila, void* pValor, int (*compara) ( void*pValor1 , void*pValor2 ) );