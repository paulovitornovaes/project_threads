#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/syscall.h>

#define MAX 100000


void *rotina(void *arg)
{
    char *string = (char *) arg;
    printf("Print do pthread_self...\n");
    printf("Olá, eu sou a %s de id %u\n\n", string, pthread_self());
    printf("\n");
    printf("Print do gettid...\n");
    printf("Olá, eu sou a %s de id %u \n\n", string, gettid());
    // a diferença entre pthread_self e gettid é que o primeiro é criado o id pelo proprio pthread_self, já o gettid cria o id com uma chamada do sistema
    
}


int main()
{
    int n;

    //vetor para guardar as threads
    pthread_t threads[MAX];

    printf("Digite a quantidade desejada de threads = ");
    scanf("%d", &n);

    
    char names[n][50];


    for (int i = 0; i < n; i++)
    {
        //laço que vai de 0 até a quantidade de threads que o usuário desejou
        //vetor para guardar a string thread_
        char name_thread[] = "Thread_";
        //vetor que vai guardar os numeros gerados de cada thread no laço
        char number_thread[MAX];
        //uso do sprintf para converter o int para char
        sprintf(number_thread, "%d", i + 1);
        //concatenar o name_thread com number_thread
        strcat(name_thread, number_thread);
        //criado um ponteiro com o thread_numero
        char *pnameThread = name_thread;
        //o vetor de vetores agora recebe o nome formado
        strcpy(names[i], pnameThread);

    }
    
    for (int i = 0; i < n; i++)
    {
        char *name_to_thread = names[i];
        //chamada do pthread create
        pthread_create(&threads[i], NULL, rotina, (void *)name_to_thread);
        //chamada do pthread_join para finalizar a thread caso ela nao tenha sido finalizada
    }
    for (int i = 0; i < n; i++)
    {
        pthread_join(threads[i], NULL);
    }
    
}