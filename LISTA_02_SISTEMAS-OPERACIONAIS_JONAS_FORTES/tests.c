#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


 void* myturn(void* arg) {
     while(1){
         sleep(1);
         printf("minha vez\n");

     }
 }

  void yourturn() {
     while(2){
         sleep(1);
         printf("sua vez\n");

     }
 }

 int main(){
     
     pthread_t newthread;
     pthread_create(&newthread, NULL, myturn, NULL);
     
     yourturn();

 return 0;
 }

