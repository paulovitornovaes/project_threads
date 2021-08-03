#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(){
    
    int id = fork();
    if (id == 0)
    {
        sleep(1);
    }
    
    printf("Current ID : %d, Parent ID : %d\n", getpid(), getppid());
    return 0;
}