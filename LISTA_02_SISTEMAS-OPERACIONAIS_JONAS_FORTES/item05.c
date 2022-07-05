/*
author: Gabriel 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

void mostrarDiretorio(const char *path){

	DIR *d = opendir(path);
	//Criação de um ponteiro
	struct dirent *dir;
	
	char arquivoNome[256];
	
	//Verificar caso o diretório não exista
	if(d == NULL){
		printf("Erro! Nao foi possivel abrir o diretorio %s\n", path);
		return;
	}
	printf("Conteudo do Diretorio %s\n", path);
	//Percorre o diretório e imprime os arquivos
	while ((dir = readdir(d)) != NULL){
		printf(">> %s\n", dir->d_name);	
		if(arquivoNome[0] == '.') continue;
		printf("%s\n", arquivoNome);
	}
	//Fecha o diretório
	closedir(d);
}



int main(int argc, char *argv[]){

	int i;
	//Laço de repedição para percorrer todos os argumentos
	for(i = 1; i<argc; i++){
	mostrarDiretorio(argv[i]);
	}
	return 0;
}
