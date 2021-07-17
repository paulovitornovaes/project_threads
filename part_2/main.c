#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define MAX 3

int tamanho = MAX;

//FUNÇÃO SEM SEMAFORO, TIROU OS NUMEROS PARES CERTINHO
void *remove_par_only_thread(void *arg)
{

    
    int *numero = (int *)arg;
    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        if (numero[i] % 2 == 0)
        {
            for (int j = i; j < MAX; j++)
            {
                numero[j] = numero[j + 1];
                tamanho--;
            }
        }
    }
    return NULL;
    //funcionou OK
}

//FUNÇÃO COM THREAD E SEM SEMAFORO, TIROU OS NUMEROS PARES CERTINHO
void *remove_par(void *arg)
{
    int *numero = (int *)arg;
    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        if (numero[i] % 2 == 0)
        {
            for (int j = i; j < MAX; j++)
            {
                numero[j] = numero[j + 1];
            }
        }
    }
}

void *remove_multiplo_only_thread(void *arg)
{
    int *numero = (int *)arg;

}

int main()
{
    //criando tipo thread
    pthread_t thread_1, thread_2;

    //criando um vetor de inteiros
    int vetor_inteiros[MAX];

    //iniciando o semaforo

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

    int tamanho_novo = (int *) (pthread_create(&thread_1, NULL, &remove_par_only_thread, (void *)vetor_inteiros));

    printf("TAMANHO MAIN = %d\n", tamanho_novo);

    printf("Vetor com a função que remove pares->\n");
    for (int i = 0; i < MAX; i++)
    {
        printf("[%d]\n", vetor_inteiros[i]);
    }

    return 0;
}