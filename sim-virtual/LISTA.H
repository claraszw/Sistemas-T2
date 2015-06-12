#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: INF 1301 Automatização dos testes de módulos C
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*			cs  -  Clara Szwarcman
*			gs  -  Guilherme Simas
*			lb  -  Lucas Borges
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*	  5		 csgslb 03/set/2014 padronização de retornos para teste automatizado
*								e dos nomes das funções
*     4       avs   01/fev/2006 criar linguagem script simbólica
*     3       avs   08/dez/2004 uniformização dos exemplos
*     2       avs   07/jul/2003 unificação de todos os módulos em um só projeto
*     1       avs   16/abr/2003 início desenvolvimento
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetListaNaoExiste ,
               /* A lista não existe */

         LIS_CondRetFaltouMemoria ,
               /* Faltou memória ao tentar criar um elemento de lista */
		 
   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ppLista - referência para ponteiro da lista a ser criada
*
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     LIS_CondRetOK            - criou lista sem problemas
*     LIS_CondRetFaltouMemoria - faltou memória ao alocar espaço
*
***********************************************************************/

   LIS_tpCondRet LIS_CriarLista( LIS_tppLista* pLista ,
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $FV Valor retornado
*     LIS_CondRetOK             - esvaziou sem problemas
*	  LIS_CondRetListaNaoExiste - ponteiro da lista é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK              - inseriu antes sem problemas
*	  LIS_CondRetListaNaoExiste  - ponteiro da lista é NULL
*     LIS_CondRetFaltouMemoria   - faltou memória ao alocar espaço
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento após o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado     
*     LIS_CondRetOK              - inseriu após sem problemas
*	  LIS_CondRetListaNaoExiste  - ponteiro da lista é NULL
*     LIS_CondRetFaltouMemoria   - faltou memória ao alocar espaço
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento a esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK              - excluiu elemento sem problemas
*     LIS_CondRetListaVazia      - lista é vazia
*	  LIS_CondRetListaNaoExiste  - ponteiro da lista é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista de onde se quer o valor
*     ppValor - referência para ponteiro que receberá o ponteiro do elemento
*
*  $FV Valor retornado
*     LIS_CondRetOK              - obteve referência para elemento sem problemas
*     LIS_CondRetListaVazia      - lista é vazia
*	  LIS_CondRetListaNaoExiste  - ponteiro da lista é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_ObterValor( LIS_tppLista pLista , void ** ppValor) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*		LIS_CondRetOK              - foi para elemento inicial sem problemas
*       LIS_CondRetListaVazia      - lista é vazia
*		LIS_CondRetListaNaoExiste  - ponteiro da lista é NULL
*
***********************************************************************/

    LIS_tpCondRet LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $FV Valor retornado
*		LIS_CondRetOK              - foi para elemento final sem problemas
*       LIS_CondRetListaVazia      - lista é vazia
*		LIS_CondRetListaNaoExiste  - ponteiro da lista é NULL
*
***********************************************************************/

   LIS_tpCondRet LIS_IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     CondRetOK             - se numElem elementos tiverem sido andados
*     CondRetFimLista       - se encontrou o fim da lista antes de andar numElem
*                             elementos
*     CondRetListaVazia     - se a lista está vazia
*	  CondRetListaNaoExiste - se a lista não existir
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;

/***********************************************************************
*
*  $FC Função: LIS  &Alterar Valor do Elemento Corrente
*
*  $ED Descrição da função
*	   Altera o ponteiro contido  no elemento corrente.
*	   O espaço referenciado pelo ponteiro original não é
*	   desalocado.
*     
*  $EP Parâmetros
*     pLista     - ponteiro para a lista a ser manipulada
*     pValorNovo - ponteiro a ser inserido no elemento corrente
*
*  $FV Valor retornado  
*     CondRetOK             - o valor do elemento corrente foi alterado sem problemas
*     CondRetListaVazia     - lista é vazia
*	  CondRetListaNaoExiste - ponteiro da lista é NULL
*     
***********************************************************************/

   LIS_tpCondRet LIS_AlterarValor( LIS_tppLista pLista ,
                                          void * pValorNovo        ) ;



   //---------------------------------------------------------------------------------------------------------------
   //função implementada pq endler

   int LIS_ObtemNumElementos(LIS_tppLista pLista);


#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
