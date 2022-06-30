#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char *argv[]){

    pid_t pid;
    int i;

    if((pid = fork()) < 0){
        perror("Erro!");
        exit(1);
    }
    else if (pid == 0){
        //Execução primeira metade pelo processo filho
        printf("Processo Filho. PID: %d\n", getpid());
        for(i=1; i <= argc/2; i++){ 
            printf("%s ", argv[i]);
        }
        printf("\nFIM Processo Filho\n");
        
    }else{
        //Execução segunda metade pelo processo pai
        printf("Processo Pai. PID: %d\n", getpid());
        wait(0); // espera o Filho terminar
        for(i=(argc/2)+1; i < argc; i++){ 
            printf("%s ", argv[i]);
        }
        printf("\nFIM Processo Pai\n");
    }
    
    return 0;
}