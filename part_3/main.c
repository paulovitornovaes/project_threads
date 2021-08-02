#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define MAX 1000000

struct vetor_dados
{
    int vetor[MAX];
    int tamanho;
};


void *gera_vetor_random(int *vetor_inteiros)
{
    //chamada do srand para auxiliar na criação de numeros randomicos
    srand(time(NULL));
    //looping de indice 0 até o valor MAX
    printf("Vetor com 100000 inteiros ->\n");
    for (int i = 0; i < MAX; i++)
    {
        //vetor de inteiros recebe o numero aleatorio de 0 a 100
        vetor_inteiros[i] = rand() % 100 + 1;

        printf("[%d]\n", vetor_inteiros[i]);
    }
    printf("\n");

    return NULL;
}


int main(){
    int id = fork();
    
    struct vetor_dados vetor_inteiros;
    vetor_inteiros.tamanho = MAX;

    gera_vetor_random(vetor_inteiros.vetor);

    return 0;
}