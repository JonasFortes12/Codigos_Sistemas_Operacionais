
//execucao: gcc -pthread -o item02 item02.c -lm

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>

#define N 9 //loops

double reultSum = 0, resultSubt = 0;

// Fatorial
unsigned long long int factorial(int number){
    unsigned long long int value; 
    if (number == 0 || number == 1){
        return 1;
    }else{
        value = number * factorial(number - 1);
        return value; 
    }
}

// Rotina para os termos positivos da serie
void* sumRoutine(void *arg){ 
    int* x = (int*) arg; 
 
    double term, numerator;
    unsigned long long int denominator;

    for(int i = 0; i < N; i+=2){
        numerator = pow(-1, i) * pow((*x), (2*i+1));
        denominator = factorial( 2*i + 1 );
        term = numerator/denominator;

        reultSum += term; 
    }
    return NULL;
}

// Rotina para os termos negativos da serie
void* subtRoutine(void *arg){ 
    int* x = (int*) arg;  

    double term, numerator;
    unsigned long long int denominator;

    for(int i = 1; i < N; i+=2){
        numerator = pow(-1, i) * pow((*x), (2*i+1));
        denominator = factorial( 2*i + 1 );
        term = numerator/denominator;

        resultSubt += term; 
    }
    return NULL;
}

void main(){

    int x;
    pthread_t threadSumTerm, threadSubtTerm;

    printf("Digite o valor de x: ");
    scanf("%d", &x);

    pthread_create(&threadSumTerm, NULL, &sumRoutine, &x); 
    pthread_create(&threadSubtTerm, NULL, &subtRoutine, &x); 
    
    pthread_join(threadSumTerm, NULL); 
    pthread_join(threadSubtTerm, NULL);

    printf("Resultado: %f\n", (reultSum + resultSubt)); 
    
}