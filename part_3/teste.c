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

sem_t semaphore1, semaphore2;

void conserta()
{
    printf("Mecanico conserta o carro.\n");
    return 0;
}
void recebe_pedido()
{
    printf("Atendente recebe pedido.\n");
    return 0;
}
void recebe_pagamento()
{
    printf("Atendente recebe pagamento.\n");
    return 0;
}
int main()
{

    printf("iniciando o programa...\n");

    // --------------------  Criação dos structs usados ----------------- //

    struct vetor_dados vetor_inteiros;
    vetor_inteiros.tamanho = MAX;

    struct vetor_dados *pvetor_inteiros;
    pvetor_inteiros = &vetor_inteiros;

    gera_vetor_random(vetor_inteiros.vetor);

    //Fazendo uma cópia do vetor_inteiros para vetor que vamos usar sem processos
    struct vetor_dados *compara_vetor_inteiros;
    compara_vetor_inteiros = &vetor_inteiros;

    remove_mul_par(compara_vetor_inteiros);

    // ----------------------------------------------------------------- //

    // -------------------- Uso da memória compartilhada ----------------- //

    int shmid = shmget(0, 100000 * sizeof(int), 0666 | IPC_CREAT); //criado a área da memória compartilhada com key 0 / área alocada foi de 100000 pensado para tamanho do inteiro
    // EXPLICAR FLAGS 0666 IPC_CREAT

    if (shmid < 0)
    {
        perror("shmget error");
    }

    struct vetor_dados *compartilhado = shmat(shmid, NULL, 0);
    //criando a struct vetor_dados para receber esse espaço de memória partilhada

    *compartilhado = vetor_inteiros;
    //meu struct vetor_inteiros está agora na área da memória partilhada

    int id;

    if ((id = fork()) < 0)
    {
        printf("Erro no fork!\n");
        exit(1);
    }

    if (id == 0)
    {
        remove_par(compartilhado);
        exit(1);
    }
    else
    {

        wait(NULL);
        remove_mul_cinco(compartilhado);
        compara_vetor(compartilhado, compara_vetor_inteiros);
    }

    if ((shmid, IPC_RMID, &buf) == -1)
    {
        perror("main: shmctl: ");
    }

    return 0;
}
