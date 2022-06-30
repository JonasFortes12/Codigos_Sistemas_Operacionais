#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){
    pid_t pid;
    pid_t pid2;

    if((pid = fork()) < 0){
        perror("Erro!");
        exit(1);
    }
    else if (pid == 0){
        if((pid2 = fork()) < 0){
            perror("Erro!");
            exit(1);
        }
        else if (pid2 == 0){
            //Execução pelo processo filho1
            
            printf("\nExecução Processo Filho1 ->");
        }else{
            //Execução pelo processo filho
            
            wait(0);//filho espera filho1
            printf("Execução Processo Filho ->");
        }
    }else{
        //Execução processo pai
        
        wait(0);//pai espera filho
        printf("Execução Processo Pai\n");
    }
    return 0;
}