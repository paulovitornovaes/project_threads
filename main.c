#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/syscall.h>

#define MAX 10000

//função itoa que transforma int em string
char *itoa(int i, char b[])
{
    char const digit[] = "0123456789";
    char *p = b;
    if (i < 0)
    {
        *p++ = '-';
        i *= -1;
    }
    int shifter = i;
    do
    { //Move to where representation ends
        ++p;
        shifter = shifter / 10;
    } while (shifter);
    *p = '\0';
    do
    { //Move back, inserting digits as u go
        *--p = digit[i % 10];
        i = i / 10;
    } while (i);
    return b;
}

void *rotina(void *str)
{
    char *string = str;
    printf("Olá, eu sou a %s de id %u \n", string, pthread_self());
}

int main(int argc, char *argv[])
{
    int n;
    pthread_t threads[MAX];

    printf("digite a quantidade de threads a serem criadas = ");
    scanf("%d", &n);

    //looping para fazer a quantidade de threads necessárias
    for (int i = 0; i < n; i++)
    {
        //vetores que fiz para criar o nome da thread
        char name[MAX] = "Thread_";
        char number[MAX];

        //inteiro i transformado em char e jogado para o vetor number
        itoa(i, number);

        //concatenar as strings name e number (vai ficar salvo no primeiro parametro)
        strcat(name, number);

        //passando o vetor name como ponteiro
        char *pname = name;

        //criação da thread na posição i do vetor, passando a rotina e o argumento ponteiro pname que aponta para o name[MAX]
        pthread_create(&threads[i], NULL, &rotina, pname);

        //limpar o vetor para nao ficar adicionando o numero (ex thread_012345...)
        memset(name, 0, MAX);
    }   

    
    for (int i = 0; i < n; i++){
        pthread_join(threads[i], NULL);
    }


    return 0;
}