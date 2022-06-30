#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t pid;

    if((pid = fork()) < 0){
        perror("Erro!");
        exit(1);
    }
    else if (pid == 0){
        //Execução processo filho
        system("spotify");
        
    }
    return 0;
}