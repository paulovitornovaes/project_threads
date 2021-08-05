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

struct shmid_ds buf; // APRENDE

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

    // PARTE DA CRIAÇÃO DA MEMÓRIA COMPARTILHADA

    int *aponta;

    int shmid;
    shmid = shmget(0, 2000000, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        printf("Erro !!!\n");
        exit(-1);
    }

    struct vetor_dados *memoria_partilhada = shmat(shmid, (void *)0, 0);
    if (memoria_partilhada == (void *)-1)
    {
        printf("Erro ao fazer shmat\n");
        exit(-1);
    }

    *memoria_partilhada = vetor_inteiros;

    // ------------------------------------------------------------------ //

    int id = fork();

    sem_init(&semaphore, 1, 1);

    if (id == 0)
    {
        printf("entrando no processo filho id %d...(remove pares)\n", id);
        for (int i = 0; i < memoria_partilhada->tamanho; i++)
        {

            if (memoria_partilhada->vetor[i] % 2 == 0)
            {
                for (int j = i; j < vetor_inteiros.tamanho - 1; j++)
                {
                    memoria_partilhada->vetor[j] = memoria_partilhada->vetor[j + 1];
                }
                memoria_partilhada->tamanho--;
                i--;
            }
        }
    }

    else
    {

        printf("entrando no processo pai id %d...(remove multiplos de 5)\n", id);
        for (int i = 0; i < vetor_inteiros.tamanho; i++)
        {

            if (memoria_partilhada->vetor[i] % 5 == 0)
            {
                for (int j = i; j < memoria_partilhada->tamanho - 1; j++)
                {
                    memoria_partilhada->vetor[j] = memoria_partilhada->vetor[j + 1];
                }
                memoria_partilhada->tamanho--;
                i--;
            }
        }
    }

    printf("Novo vetor formado -> \n");
    imprime_vetor(*memoria_partilhada);
    printf("\n");

    sem_destroy(&semaphore);

    if (shmctl(shmid, IPC_RMID, &buf) == -1)
    {
        perror("main: shmctl: ");
        exit(1);
    }

    return 0;
}
