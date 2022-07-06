/*
author: Gabriel 
*/

#define _XOPEN_SOURCE 700

#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int mostrarEntrada(const char *filepath, const struct stat *info, const int typeflag, struct FTW *pathinfo){

	const double bytes = (double)info->st_size; //Verificando o tamanho

	if (bytes >= 1099511627776.0) //Caso seja >= a 1 terabyte
		printf(" %9.3f TB", bytes / 1099511627776.0);
	else
	if (bytes >= 1073741824.0) //Caso seja >= a 1 gigabyte
		printf(" %9.3f GB", bytes / 1073741824.0);
	else
	if (bytes >= 1048576.0) //Caso seja >= a 1 megabyte
		printf(" %9.3f MB", bytes / 1048576.0);
	else
	if (bytes >= 1024.0) //Caso seja >= a 1 kilobyte
		printf(" %9.3f KB", bytes / 1024.0);
	else
		printf(" %9.0f B  ", bytes);
		 
	//Análise do tipo de arquivo a ser lido
	if (typeflag == FTW_F) //Caso seja um arquivo regular
		printf(" %s\n", filepath);
	else
	if (typeflag == FTW_D || typeflag == FTW_DP) //Caso seja um Diretório
		printf(" %s/\n", filepath);
	else
	if (typeflag == FTW_DNR) //Caso seja um diretório que não pode ser lido
		printf(" %s/ (Ilegivel)\n", filepath);
	else
		printf(" %s (Desconhecido)\n", filepath);

	return 0;
}

int mostrarArvoreDiretorio(const char *const dirpath){
	int result;

    /* Invalid directory path? */
	if (dirpath == NULL || *dirpath == '\0')
		return errno = EINVAL; //Argumento inválido
		
	//A função nftw percorre recursivamente a hierarquia de diretórios
	result = nftw(dirpath, mostrarEntrada, 15, FTW_PHYS);
	/*Argumentos: 
	1° = Nome do caminho do objeto
	2° = Ponteiro para o stat buffer (Nesse caso a saida da função mostrarEntrada)
	3° = Um inteiro que fornece informações adicionais
	4° = Um ponteiro para uma extrutura FTW
	*/
	if (result >= 0)
		errno = result;
		
	return errno;
}

int main(int argc, char *argv[]){

	int arg;

	if (argc < 2) { //Caso nenhum caminho seja passado o código usa o caminho do diretório atual
		if (mostrarArvoreDiretorio(".")) {
			fprintf(stderr, "%s.\n", strerror(errno));
			return EXIT_FAILURE;
		}
	} else { //Caso um caminho seja passado o códiigo percorre ele
		for (arg = 1; arg < argc; arg++) {
			if (mostrarArvoreDiretorio(argv[arg])) {
			fprintf(stderr, "%s.\n", strerror(errno));
			return EXIT_FAILURE;
			}
		}
	}
	return EXIT_SUCCESS;
}