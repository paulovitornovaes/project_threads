#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define MAX 5

void *remove_par(void *arg){
    int numero = (int *) arg;

    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        /* code */
    }
    
    
    
    
    
}

int main()
{
    pthread_t thread_1, thread_2;
    int vetor_inteiros[MAX];

    srand(time(NULL));
    for (int i = 0; i < MAX; i++)
    {
        //vetor de inteiros recebe o numero aleatorio de 0 a 100
        vetor_inteiros[i] = rand() % 100 + 1;
        printf("vetor -> [%d]\n", vetor_inteiros[i]);
    }

    printf("\n");

    //looping reverso
    for (int i = MAX - 1; i >= 0; i--)
    {
        int *pvetor_inteiros = vetor_inteiros[i];
        
        pthread_create(&thread_1, NULL, &remove_par,(void *)pvetor_inteiros);
    }

    return 0;
}