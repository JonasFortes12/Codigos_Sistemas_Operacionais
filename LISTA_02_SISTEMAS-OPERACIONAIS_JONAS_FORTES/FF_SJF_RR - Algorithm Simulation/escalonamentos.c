#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>

/*Process Struct */
struct process{
    char id;
    int length;
    int order;
    struct process *next;  
};

typedef struct process Process;

/*Criar Processo Vazio*/
Process* newProcess(void){
    return NULL;
}

/*Liberar Processo */
void freeProcess(Process* prss){
    Process* prssAux = prss;

    while (prssAux != 0){
        Process* temp = prssAux->next;
        free(prssAux);
        prssAux = temp;
    }
}

/*Imprimir os Processos */
void printProcess(Process* prss){

    printf("Ordem dos processos:\n");
    for(Process* temp = prss; temp != NULL; temp=temp->next){
        printf("%c -> ", temp->id);
    }
    printf("FIM\n\n");
}

/*Insere o processo em ordem crescente*/
Process* insertProcess(Process* prss, int id, int lenght, int order){
    
    Process* prssPrev = NULL;//processo anterior
    Process* prssAux = prss;//processo auxiliar - percorrido

    while(prssAux != NULL && prssAux->order < order){//avanca ate achar a ordem correta
        
        prssPrev = prssAux;
        prssAux = prssAux->next;
    }

    /*Criar novo processo*/
    Process* prssNew = (Process*) malloc(sizeof(Process));
    if(prssNew == NULL){
        printf("Erro na alocacao de memória.\n");
        exit(1);
    }
    
    /*Configurando o novo processo*/
    prssNew->id = id;
    prssNew->length = lenght;
    prssNew->order = order;

    /*Adiociona o processo no encadeamento*/
    if(prssPrev == NULL){
        prssNew->next = prss;
        prss = prssNew;
    }else{
        prssNew->next = prssPrev->next;
        prssPrev->next = prssNew;
    }

    return prss;
}

/*Insere o processo em ordem de prioridade (maior processo por ultimo)*/
Process* insertShortestProcessFirst(Process* prss, int id, int lenght, int order){
    
    Process* prssPrev = NULL;
    Process* prssAux = prss;

    while(prssAux != NULL && prssAux->length < lenght){
        
        prssPrev = prssAux;
        prssAux = prssAux->next;
    }

    /*Criar novo processo*/
    Process* prssNew = (Process*) malloc(sizeof(Process));
    if(prssNew == NULL){
        printf("Erro na alocacao de memória.\n");
        exit(1);
    }
    
    /*Configurando o novo processo*/
    prssNew->id = id;
    prssNew->length = lenght;
    prssNew->order = order;

    /*Adiociona o processo no encadeamento*/
    if(prssPrev == NULL){
        prssNew->next = prss;
        prss = prssNew;
    }else{
        prssNew->next = prssPrev->next;
        prssPrev->next = prssNew;
    }

    return prss;
}

/*Função para tornar uma lista circular, girar lista*/
Process* turnRound(Process* prss){

    Process* prssAux = prss;
    Process* prssAux2 = prss;

    while(prssAux2->next != NULL) prssAux2 = prssAux2->next;

    prssAux2->next = prssAux; // o fim aponta para o inicio - fechando o circulo

    return prssAux;
}


void schedulerFIFO(Process* prss){   
}

void schedulerSJF(Process* prss){

    Process* prssAux = prss;
    Process* shortests = newProcess(); //cria uma lista de processos vazia para ordenar SJF

    while(prssAux != NULL){

        shortests = insertShortestProcessFirst(
            shortests, 
            prssAux->id, 
            prssAux->length, 
            prssAux->order);

        prssAux = prssAux->next;
    }

    printf("________ESCALONAMENTO SJF___________\n");

    for(Process* temp = shortests; temp != NULL; temp = temp->next){

        printf("Processo %c executando... [%d ut]\n", temp->id, temp->length);
        sleep((temp->length)*1000);
    }
    freeProcess(shortests);

    printf("________FIM SJF___________\n");

}

void schedulerRR(Process* prss, int quantum){  

    Process* prssAux = turnRound(prss);

    while (prssAux != NULL){
        
        if(prssAux->length != 0 && prssAux->length <= quantum){

            printf("Processo %c executando... [%d ut]\n", prssAux->id, prssAux->length);
            sleep((prssAux->length)*1000);
            prssAux->length = 0;
            
        }else if(prssAux->length > quantum){

            printf("Processo %c executando... [%d ut]\n", prssAux->id, prssAux->length);
            sleep((prssAux->length)*1000);
            prssAux->length -= quantum ;

        }else break;

        prssAux = prssAux->next;
    }
}


void main(){
    setlocale(LC_ALL, "Portuguese");

    Process* process = newProcess();
    char id;
    int numProcess, option, quantum, lenght, order;

    printf("Quantidade de processos na fila: ");
    scanf("%d",&numProcess);

    for(int i = 1; i <= numProcess; i++){ //Laço para ler os valores
        printf("Digite um identificador para o %dº processo(char): ", i);
        scanf(" %c",&id);//ERROR no codeblocks -> não executa o scanf
        printf("Digite a ordem de chegada do processo(int): ");
        scanf("%d",&order);
        printf("Digite o tempo de execucao do processo(int): ");
        scanf("%d",&lenght);

        process = insertProcess(process, id, lenght, order); //Vai inserindo os processo na lista de processos
        printf("\n");
    }

    printf("[1] - SFJ\n");
    printf("[2] - Round Robin\n");
    printf("Qual algoritmo de escalonamento deseja: ");
    scanf("%d",&option);

    switch (option){
        case 1:
            printProcess(process);
            schedulerSJF(process);
            break;
        
        case 2:
            printf("quantum: ");scanf("%d",&quantum);
            schedulerRR(process, quantum);
            break;

        default:
            printf("Opcao Invalida\n");
            break;
    }

    freeProcess(process);
    printf("\n");

}
