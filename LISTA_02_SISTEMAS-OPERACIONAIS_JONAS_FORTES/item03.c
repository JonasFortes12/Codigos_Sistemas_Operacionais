/*
author: Gabriel 
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

int numPrimo = 0; //Armazena o número de primos

//Função para saber se o númeor é primo
int ehPrimo(int n) {
	int i, cont = 0;

	for(i = 1; i <= n; i++) {
		if (n % i == 0) {
		cont++;
		}
	}

	if (cont == 2) {
		return 1; //quando for primo
	} else {
		return 0; //quando não for primo
	}
}

//Função para contar a quantidade de primos de N/2 até 0
void *qntPrimo1(void *num){
	
	int *n = (int *) num;

	int cont; 
	int contPrimo = 0; 
	
	for(cont = 2; cont <= (*n/2); cont++){
		if(ehPrimo(cont) != 0){
			contPrimo++;
		}
	}numPrimo = numPrimo + contPrimo;
}

//Função para contar a quantidade de primos de N até N/2 + 1
void *qntPrimo2(void *num){
	
	int *n = (int *) num;

	int cont;
	int contPrimo = 0;
	
	for(cont = (*n/2)+1; cont <= *n; cont++){
		if(ehPrimo(cont) != 0){
			contPrimo++;
		}
	}numPrimo = numPrimo + contPrimo;
}


int main(int argc, char *argv[]){

	int n;
	pthread_t thread1, thread2;
	printf("Digite um numero: ");
	scanf("%d", &n);
	
	pthread_create(&thread1, NULL, qntPrimo1, &n);
	pthread_create(&thread2, NULL, qntPrimo2, &n);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
    
	printf("Quantidade de numeros primos = %d\n", numPrimo);
	
	return 0;

}