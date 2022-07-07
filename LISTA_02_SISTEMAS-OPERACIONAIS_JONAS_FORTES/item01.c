#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define N 10 //quantidade threads filhas
 
pthread_t tid[N];
pthread_t father;
 
 
void* helloThread(void* arg){
 
    int num = *((int*)arg);
 
    printf("Alo do Filho [%d]\n", num);
    for(int j = 0; j<(0x0FFFFFFF); j++);
    printf("Thal do Filho [%d]\n", num);
 
    free(arg);
    return NULL;
}
 
void main(void* arg){
 
    printf("Alo do Pai\n");
   
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
   
    for(int j = 0; j<(0x0FFFFFFF); j++);
    printf("Thal do Pai\n");
 
}

