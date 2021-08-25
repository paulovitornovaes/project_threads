#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#define MAX 100000

sem_t semaphore;

struct vetor_dados
{
    int vetor[MAX];
    int tamanho;
};

//                         FUNÇÕES AUXILIARES                  //

void *gera_vetor_random(int *vetor_inteiros)
{
    srand(time(NULL));

    for (int i = 0; i < MAX; i++)
    {
        vetor_inteiros[i] = rand() % 100 + 1;

    }

    return NULL;
}

void *imprime_vetor(struct vetor_dados vetor_inteiros)
{
    for (int i = 0; i < vetor_inteiros.tamanho; i++)
    {
        printf("[%d]\n", vetor_inteiros.vetor[i]);
    }

    return NULL;
}

void *compara_vetor(struct vetor_dados *vetor_inteiros_comparador, struct vetor_dados *vetor_inteiros_thread_sem)
{
    int key = 0;
    if (vetor_inteiros_comparador->tamanho == vetor_inteiros_thread_sem->tamanho)
    {
        for (int i = 0; i < vetor_inteiros_comparador->tamanho; i++)
        {
            if (vetor_inteiros_comparador->vetor[i] != vetor_inteiros_thread_sem->vetor[i])
            {
                key += 1;
            }
        }
    }
    else
    {
        printf("thread -> %d sequencial -> %d\n", vetor_inteiros_comparador->tamanho, vetor_inteiros_thread_sem->tamanho);
    }
    
    printf("Foram encontrados %d diferenças entre os vetores\n", key);

    return NULL;
}

// --------------------------------------------------------- //



//                         FUNÇÕES SEQUENCIAIS                //

void *remove_par(struct vetor_dados *vetor_inteiros)
{
    int maximo = vetor_inteiros->tamanho;

    for (int i = maximo - 1; i >= 0; i--)
    {
        if (vetor_inteiros->vetor[i] % 2 == 0)
        {
            for (int j = i; j < maximo; j++)
            {
                vetor_inteiros->vetor[j] = vetor_inteiros->vetor[j + 1];
            }
            maximo--;
        }
    }
    vetor_inteiros->tamanho = maximo;

    return NULL;
}

void *remove_mul_cinco(struct vetor_dados *vetor_inteiros)
{
    int maximo = vetor_inteiros->tamanho;
    for (int i = maximo - 1; i >= 0; i--)
    {
        if (vetor_inteiros->vetor[i] % 5 == 0)
        {

            for (int j = i; j < maximo; j++)
            {
                vetor_inteiros->vetor[j] = vetor_inteiros->vetor[j + 1];
            }
            maximo--;
        }
    }
    vetor_inteiros->tamanho = maximo;

    return NULL;
}

// --------------------------------------------------------- //



//FUNÇÕES COM USO DE THREAD E SEMÁFORO //

void *remove_par_thread_sem(void *arg)
{
    struct vetor_dados *arg_dados = (struct vetor_dados *)arg;
    int maximo = arg_dados->tamanho;
    for (int i = maximo - 1; i >= 0; i--)
    {
        sem_wait(&semaphore);
        if (arg_dados->vetor[i] % 2 == 0)
        {
            for (int j = i; j < maximo; j++)
            {
                arg_dados->vetor[j] = arg_dados->vetor[j + 1];
            }
            maximo--;
        }
        sem_post(&semaphore);
    }
    arg_dados->tamanho = maximo;
    return NULL;
}

void *remove_mul_cinco_thread_sem(void *arg)
{
    struct vetor_dados *arg_dados = (struct vetor_dados *)arg;
    int maximo = arg_dados->tamanho;
    for (int i = maximo - 1; i >= 0; i--)
    {
        sem_wait(&semaphore);
        if (arg_dados->vetor[i] % 5 == 0)
        {

            for (int j = i; j < maximo; j++)
            {
                arg_dados->vetor[j] = arg_dados->vetor[j + 1];
            }
            maximo--;
        }

        sem_post(&semaphore);
    }
    arg_dados->tamanho = maximo;
    return NULL;
}
// ---------------------------------- //


int main()
{
    pthread_t thread_1, thread_2;
    clock_t t_sequencial, t_thread_sem;

    struct vetor_dados vetor_inteiros;
    vetor_inteiros.tamanho = MAX;
    struct vetor_dados *pvetor_original = &vetor_inteiros;

    gera_vetor_random(vetor_inteiros.vetor);

    struct vetor_dados vetor_sequencial = vetor_inteiros;
    struct vetor_dados *pvetor_sequencial = &vetor_sequencial;

    struct vetor_dados vetor_thread_sem = vetor_inteiros;
    struct vetor_dados *pvetor_thread_sem = &vetor_thread_sem;

    struct vetor_dados vetor_comparador = vetor_inteiros;
    struct vetor_dados *pvetor_comparador = &vetor_comparador;

    printf("Caso necessite de imprimir os valores, use a função imprime_vetor()\nIniciando programa...\n");


    //                  IMPLEMENTAÇÃO THREAD - SEMAFORO                     //

    t_thread_sem = clock();

    sem_init(&semaphore, 0, 1);
    pthread_create(&thread_1, NULL, &remove_par_thread_sem, (void *)pvetor_thread_sem);
    pthread_create(&thread_2, NULL, &remove_mul_cinco_thread_sem, (void *)pvetor_thread_sem);

    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);

    t_thread_sem = clock() - t_thread_sem;

    printf("Tempo de execucao com threads e semáforo: %lf\n", ((double)t_thread_sem) / ((CLOCKS_PER_SEC)));

    // -------------------------------------------------------------------- //

    // -------------------------------------------------------------------- //

    //                  IMPLEMENTAÇÃO SEQUENCIAL                           //


    t_sequencial = clock();

    remove_par(pvetor_sequencial);
    remove_mul_cinco(pvetor_sequencial);

    t_sequencial = clock() - t_sequencial;
    printf("Tempo de execucao sem threads: %lf\n", ((double)t_sequencial) / ((CLOCKS_PER_SEC)));
    // -------------------------------------------------------------------- //

    sem_destroy(&semaphore);



    for (int i = 0; i < vetor_comparador.tamanho; i++)
    {
        if (vetor_comparador.vetor[i] % 2 == 0 || vetor_comparador.vetor[i] % 5 == 0)
        {
            for (int j = i; j < vetor_comparador.tamanho - 1; j++)
            {
                vetor_comparador.vetor[j] = vetor_comparador.vetor[j + 1];
            }
            vetor_comparador.tamanho--;
            i--;
        }
    }

    
    compara_vetor(pvetor_comparador, pvetor_thread_sem);

    return 0;
}