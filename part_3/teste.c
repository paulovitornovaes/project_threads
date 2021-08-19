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
    sem_init(&semaphore1, 1, 0);
    sem_init(&semaphore2, 0, 0);
    for (int i = 0; i < 5; i++)
    {
        sem_wait(&semaphore1);
        conserta();
        sem_wait(&semaphore2);
        recebe_pedido();
        recebe_pagamento();
        sem_post(&semaphore2);
        sem_post(&semaphore1);
    }
}
