#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct quadro_fisico
{
    int R;
    int M;
    unsigned int endereco;
    int time;

}Quadro_fisico;

void trata_NRU(FILE * fonte, int num_max);

void trata_LRU(FILE * fonte, int num_max);

void trata_SEG(FILE * fonte, int num_max);

int main(int argc, char *argv[])
{
    int num_max, ocupados=0;
    int tam_pag=atoi(argv[3]), tam_mem=atoi(argv[4]);
    FILE * fonte = fopen(argv[2],"r");

    if(fonte==NULL)
    {
        printf("Arquivo nao encontrado\n");
        exit(1);
    }

    num_max=tam_mem/tam_pag;

    if(strcmp("NRU", argv[1])==0)
        trata_NRU(fonte,num_max);
    else if(strcmp("LRU", argv[1])==0)
        trata_NRU(fonte,num_max);
    else if(strcmp("SEG", argv[1])==0)
        trata_NRU(fonte,num_max);

    fclose(fonte);

    return 0;
}
