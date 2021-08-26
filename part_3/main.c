#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <sys/ipc.h>

#define MAX 100000

struct shmid_ds buf;

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

    //printf("Vetor com 100000 inteiros ->\n");
    for (int i = 0; i < MAX; i++)
    {
        //vetor de inteiros recebe o numero aleatorio de 0 a 100
        vetor_inteiros[i] = rand() % 100 + 1;

        //printf("[%d]\n", vetor_inteiros[i]);
    }
    //printf("\n");

    return NULL;
}

void *imprime_vetor(struct vetor_dados vetor_inteiros)
{
    for (int i = 0; i < vetor_inteiros.tamanho; i++)
    {
        printf("[%d]\n", vetor_inteiros.vetor[i]);
    }
}

void *compara_vetor(struct vetor_dados *vetor_inteiros_comparador, struct vetor_dados *vetor_inteiros)
{
    int key = 0;
    if (vetor_inteiros_comparador->tamanho == vetor_inteiros->tamanho)
    {
        for (int i = 0; i < vetor_inteiros_comparador->tamanho; i++)
        {
            if (vetor_inteiros_comparador->vetor[i] != vetor_inteiros->vetor[i])
            {
                key += 1;
            }
        }
    }
    else
    {
        printf("thread -> %d sequencial -> %d\n", vetor_inteiros_comparador->tamanho, vetor_inteiros->tamanho);
    }

    printf("Foram encontrados %d diferenças entre os vetores\n", key);

    return NULL;
}

void *remove_par(struct vetor_dados *vetor_inteiros)
{
    int maximo = vetor_inteiros->tamanho;

    //looping reverso
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
    //looping reverso
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

void *remove_mul_par(struct vetor_dados *vetor_inteiros)
{
    for (int i = 0; i < vetor_inteiros->tamanho; i++)
    {
        if ((vetor_inteiros->vetor[i] % 5 == 0) || (vetor_inteiros->vetor[i] % 2 == 0))
        {
            for (int j = i + 1; j < vetor_inteiros->tamanho; j++)
            {
                vetor_inteiros->vetor[j - 1] = vetor_inteiros->vetor[j];
            }
            i--;
            vetor_inteiros->tamanho--;
        }
    }
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

    struct vetor_dados *compara_vetor_inteiros;
    compara_vetor_inteiros = &vetor_inteiros;

    remove_mul_par(compara_vetor_inteiros);

    // ----------------------------------------------------------------- //

    // -------------------- Uso da memória compartilhada ----------------- //

    int shmid = shmget(0, 100000 * sizeof(int), 0600 | IPC_CREAT | IPC_EXCL); 

    if (shmid < 0)
    {
        perror("shmget error");
    }

    struct vetor_dados *compartilhado = shmat(shmid, NULL, 0);

    *compartilhado = vetor_inteiros;

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
