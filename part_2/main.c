#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define MAX 1000000
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

void printa_novo_vetor(struct vetor_dados *vetor_inteiros)
{
    printf("Vetor apos a remoção->\n");
    for (int i = 0; i < vetor_inteiros->tamanho; i++)
    {
        printf("[%d]\n", vetor_inteiros->vetor[i]);
    }
    printf("\n");
    printf("\n");
}

//FUNÇÕES COM USO APENAS DE THREAD //
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

void *remove_mul_cinco(void *arg)
{
    struct vetor_dados *arg_dados = (struct vetor_dados *)arg;

    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        if (arg_dados->vetor[i] % 5 == 0)
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
// ---------------------------------- //

//FUNÇÕES COM USO DE THREAD E SEMÁFORO //
void *remove_par_semaforo(void *arg)
{
    struct vetor_dados *arg_dados = (struct vetor_dados *)arg;

    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        sem_wait(&semaphore);
        if (arg_dados->vetor[i] % 2 == 0)
        {
            arg_dados->tamanho--;
            for (int j = i; j < MAX; j++)
            {
                arg_dados->vetor[j] = arg_dados->vetor[j + 1];
            }
        }
        sem_post(&semaphore);
    }

    return NULL;
}

void *remove_mul_cinco_semaforo(void *arg)
{
    struct vetor_dados *arg_dados = (struct vetor_dados *)arg;

    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        sem_wait(&semaphore);
        if (arg_dados->vetor[i] % 5 == 0)
        {
            arg_dados->tamanho--;
            for (int j = i; j < MAX; j++)
            {
                arg_dados->vetor[j] = arg_dados->vetor[j + 1];
            }
        }
        sem_post(&semaphore);
    }

    return NULL;
}
// ---------------------------------- //

int main()
{
    pthread_t thread_1, thread_2;
    struct vetor_dados vetor_inteiros;
    vetor_inteiros.tamanho = MAX;

    clock_t t;

    t = clock();

    sem_init(&semaphore, 0, 1);

    gera_vetor_random(vetor_inteiros.vetor);

    pthread_create(&thread_1, NULL, &remove_par, &vetor_inteiros);

    struct vetor_dados *ponteiro_vetor_dados = &vetor_inteiros;

    pthread_create(&thread_2, NULL, &remove_mul_cinco, &vetor_inteiros);

    printa_novo_vetor(ponteiro_vetor_dados);

    sem_destroy(&semaphore);


    t = clock()- t;

    printf("Tempo de execucao: %lf", ((double)t)/((CLOCKS_PER_SEC)));
    return 0;
}