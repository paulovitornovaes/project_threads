#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define MAX 5

struct vetor_dados
{
    int vetor[MAX];
    int tamanho;
};

//FUNÇÃO COM THREAD E SEM SEMAFORO, TIROU OS NUMEROS PARES CERTINHO
void *remove_par(void *arg)
{
    struct vetor_dados *arg_dados = (struct vetor_dados *)arg;

    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        if (arg_dados->vetor[i] % 2 == 0)
        {
            arg_dados->tamanho--;
            for (int j = i; j < MAX; j++)
            {
                arg_dados->vetor[j] = arg_dados->vetor[j + 1];
            }
        }
    }

    return NULL;
}

void *gera_vetor_random(int *vetor_inteiros)
{
    //chamada do srand para auxiliar na criação de numeros randomicos
    srand(time(NULL));
    //looping de indice 0 até o valor MAX
    printf("Vetor de inteiros MAIN ->\n");
    for (int i = 0; i < MAX; i++)
    {
        //vetor de inteiros recebe o numero aleatorio de 0 a 100
        vetor_inteiros[i] = rand() % 100 + 1;

        printf("[%d]\n", vetor_inteiros[i]);
    }
    printf("\n");

        return NULL;
}

int main()
{
    pthread_t thread_1, thread_2;
    struct vetor_dados vetor_inteiros;
    vetor_inteiros.tamanho = MAX;
    int *pvetor_inteiros = vetor_inteiros.vetor;

    gera_vetor_random(pvetor_inteiros);

    pthread_create(&thread_1, NULL, &remove_par, &vetor_inteiros);

    printf("Vetor com a função que remove pares->\n");
    for (int i = 0; i < vetor_inteiros.tamanho; i++)
    {
        printf("[%d]\n", vetor_inteiros.vetor[i]);
    }

    return 0;
}