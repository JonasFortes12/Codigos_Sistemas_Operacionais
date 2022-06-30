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
        //Execução pelo processo filho
        for(int i=1; i < argc; i++){ 
            printf("Executa %s \n", argv[i]);
            system(argv[i]);
        }
    }else{
        //Execução pelo processo pai
        wait(0);//espera o processo filho, ou seja, o término dos comandos
    }

    return 0;
}
