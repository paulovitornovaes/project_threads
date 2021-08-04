#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <semaphore.h>
#define MAX 5
sem_t semaphore;

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

void *imprime_vetor(struct vetor_dados vetor_inteiros)
{
    for (int i = 0; i < vetor_inteiros.tamanho; i++)
    {
        printf("[%d]\n", vetor_inteiros.vetor[i]);
    }
}

int main()
{

    printf("iniciando o programa...\n");
    struct vetor_dados vetor_inteiros;
    vetor_inteiros.tamanho = MAX;
    gera_vetor_random(vetor_inteiros.vetor);

    //int id = fork();
    //sem_init(&semaphore, 0, 1);

    printf("entrando no processo filho...(remove pares)\n");
    for (int i = 0; i < vetor_inteiros.tamanho; i++)
    {
        //sem_wait(&semaphore);
        if (vetor_inteiros.vetor[i] % 2 == 0)
        {
            for (int j = i; j < vetor_inteiros.tamanho - 1; j++)
            {
                vetor_inteiros.vetor[j] = vetor_inteiros.vetor[j + 1];
            }
            vetor_inteiros.tamanho--;
            i--;
        }
        //sem_post(&semaphore);
    }

    printf("entrando no processo pai...(remove multiplos de 5)\n");
    for (int i = 0; i < vetor_inteiros.tamanho; i++)
    {
        //sem_wait(&semaphore);

        if (vetor_inteiros.vetor[i] % 5 == 0)
        {
            for (int j = i; j < vetor_inteiros.tamanho - 1; j++)
            {
                vetor_inteiros.vetor[j] = vetor_inteiros.vetor[j + 1];
            }
            vetor_inteiros.tamanho--;
            i--;
        }
        //sem_post(&semaphore);
    }

    imprime_vetor(vetor_inteiros);
    sem_destroy(&semaphore);

    return 0;
}
