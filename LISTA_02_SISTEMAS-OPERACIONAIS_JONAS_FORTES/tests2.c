// Compilar: gcc -pthread -o tests tests.c
// Executar: ./tests
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


void* myturn(void* arg) {
    
    int *iptr = (int*) malloc(sizeof(int));
    *iptr = 5;
    
    for(int i = 0; i < 8; i++){
        sleep(1);
        printf("minha vez %d %d\n", i, *iptr);

        (*iptr)++;

    }
    return iptr;
}

void yourturn() {
    
    for(int i = 0; i < 3; i++){
        sleep(2);
        printf("sua vez\n");

    }
}

int main(){
    
    pthread_t newthread;
    int v = 5;

    int *returnVal;

    pthread_create(&newthread, NULL, myturn, &v);
     
    yourturn();

    //Espera ate a ultima thread acabar para sair da execuao main
    pthread_join(newthread, (void*) &returnVal);

    printf("Thread acabou: *retorno=%d\n", *returnVal);

    return 0;
}

