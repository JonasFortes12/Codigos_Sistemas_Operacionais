#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include<string.h>

const int N = 10;//quantidade threads
pthread_t tid[10];


void* helloThread(void* arg){

    int num = *((int*)arg);

    pthread_t id = pthread_self();

    if(pthread_equal(id, tid[0])){
        printf("Alo do Pai\n");
        for(int j = 0; j<(0xFFFFFFFF); j++);//simular processamento
        printf("Thal do Pai\n");
       
    }else{
        printf("Alo do Filho [%d]\n", num);
        for(int j = 0; j<(0xFFFFFFFF); j++);
        printf("Thal do Filho [%d]\n", num);
    }
    
    free(arg);
    return NULL;
}

void main(){

    for(int i = 0; i < N; i++){
        
        int* num = malloc(sizeof(int));
        *num = i;
        
        if (pthread_create( &(tid[i]), NULL, &helloThread, num) != 0)
            printf("\ncan't create thread[%d]", i);
    }

    for(int i = 0; i < N; i++){
        if (pthread_join(tid[i], NULL) != 0)
            printf("\ncan't join thread[%d]", i);
    }
}
