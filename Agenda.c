#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void **pBuffer;
int *rodando;
int ordemAlfa(char* nm1, char* nm2);
void menu();

int main()
{
    rodando = (int *)malloc(sizeof(int));
    *rodando = 0;
    pBuffer = malloc(sizeof(void**));
    *pBuffer = NULL;
    
    while (*rodando == 0)
        menu();
    
    free(rodando);
    free(pBuffer);
    return 0;
}

void * newNode(char* nome, int* idade, int* telefone){
    void * nodo = (void *)calloc(1, sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**) * 2);

    char * pNome = (char *)nodo;
    int * pIdade = (int *)(nodo + sizeof(char) * 11);
    int * pTelefone =  (int *)(nodo + sizeof(char) * 11 + sizeof(int));
    void ** pAnt = (void **)(nodo + sizeof(char) * 11 + sizeof(int) + sizeof(int));
    void ** pProx = (void **)(nodo + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
    
    memcpy(pNome, nome, strlen(nome));
    *pIdade = *idade;
    *pTelefone = *telefone;
    *pAnt = NULL;
    *pProx = NULL;
	return nodo;
}

void addContato(char* nome, int* idade, int* telefone, void ** head)
{
    void *nodo = newNode(nome, idade, telefone);
    void **ant, **atual;
    ant = malloc(sizeof(void**));
    atual = malloc(sizeof(void**));
    *ant = NULL;
    *atual = (void*)*head;

    void ** pAnt = (void **)(nodo + sizeof(char) * 11 + sizeof(int) + sizeof(int));
    void ** pProx = (void **)(nodo + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
    
    if (*head == NULL) {
        *head = nodo;
        free(ant);
        free(atual);
        return;
    }
    while (*atual != NULL && ordemAlfa(nome, (char*)*atual) >= 0) {
        *ant = *atual;
        *atual = *(void**)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
    }
    if (*ant == NULL) {
        *pProx = *atual;
        void** antAtual = (void**)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int));
        *antAtual = nodo;
        *head = nodo;
    }
    else if (*atual != NULL) { 
        void** proxAnt = (void**)(*ant + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
        *proxAnt = nodo;
        *pProx = *atual;
        void** antAtual = (void**)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int));
        *antAtual = nodo;
        *pAnt = ant;
    }
    else {
        void** proxAnt = (void**)(*ant + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
        *proxAnt = nodo;
        *pAnt = *ant;
    }

    free(ant);
    free(atual);
    return;
}

void delContato(char* nome, void** head){
    if (*head == NULL)
        return;
    
    void **ant, **atual;
    ant = malloc(sizeof(void**));
    atual = malloc(sizeof(void**));
    *ant = NULL;
    *atual = (void*)*head;

    while (*atual != NULL && ordemAlfa(nome, (char*)*atual) != 0) {
        *ant = *atual;
        *atual = *(void**)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
    }
    void ** pAnt = (void **)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int));
    void ** pProx = (void **)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
    if (*head == *atual){
        *head = *pProx;
    }
    else if (*pProx != NULL) { 
        void** proxAnt = (void**)(*ant + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
        *proxAnt = *pProx;
        void** antProx = (void**)(*pProx + sizeof(char) * 11 + sizeof(int) + sizeof(int));
        *antProx = *ant;
    }
    else if (*pAnt != NULL){
        void** proxAnt = (void**)(*ant + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
        *proxAnt = NULL;
    }
    free(ant);
    free(*atual);
    free(atual);
}

void procurarContato(void** head,char* nome){
    if (*head == NULL)
        return;
    
    void **ant, **atual;
    ant = malloc(sizeof(void**));
    atual = malloc(sizeof(void**));
    *ant = NULL;
    *atual = (void*)*head;

    while (*atual != NULL && ordemAlfa(nome, (char*)*atual) != 0) {
        *ant = *atual;
        *atual = *(void**)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
    }
    *ant = *atual;
    printf("\nContato: \n");
    printf("Nome: %s\n", (char*)*ant);
    *ant += sizeof(char) * 11;
    printf("Idade: %d\n", *(int*)*ant);
    *ant += sizeof(int);
    printf("Telefone: %i\n", *(int*)*ant);
    free(ant);
    free(atual);
}

void list(void** head, int* total){
    void **ant, **atual;
    ant = malloc(sizeof(void**));
    atual = malloc(sizeof(void**));
    *ant = NULL;
    *atual = (void*)*head;
    int *c = malloc(sizeof(int));
    *c = 0;
    while (*atual != NULL && *total > *c) {
        *ant = *atual;
        printf("\nContato: \n");
        printf("Nome: %s\n", (char*)*(void**)ant);
        *ant += sizeof(char) * 11;
        printf("Idade: %d\n", *(int*)*ant);
        *ant += sizeof(int);
        printf("Telefone: %i\n", *(int*)*ant);
        *atual = *(void**)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
        (*c)++;
    }
    free(c);
    free(ant);
    free(atual);
}

int ordemAlfa(char* nm1, char* nm2){
    while (*nm1 && *nm2 && *nm1 == *nm2) {
        nm1++;
        nm2++;
    }
    int *res = malloc(sizeof(int));
    *res = (*nm1 - *nm2);

    if (*res < 0){
        free(res);
        return -1;
    }
    else if (*res > 0)
    {
        free(res);
        return 1;
    }

    free(res);
    return 0;
}

void freeList(void** head){
    void **ant, **atual;
    ant = malloc(sizeof(void**));
    atual = malloc(sizeof(void**));
    *ant = NULL;
    *atual = (void*)*head;

    while (*atual != NULL) {
        *ant = *atual;
        *atual = *(void**)(*atual + sizeof(char) * 11 + sizeof(int) + sizeof(int) + sizeof(void**));
        free(*ant);
    }
    free(ant);
    free(atual);
}

void menu()
{
    printf("Escolha uma das opcoes abaixo: \n");
    printf("1 Adicionar um Contato:  \n");
    printf("2 Listar Contatos: \n");
    printf("3 Procurar nome de um Contato: \n");
    printf("4 Remover um Contato: \n");
    printf("5 Sair: \n");

    int opcao = 0;
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        printf("Digite o nome: ");
        int *idade = malloc(sizeof(int));
        int *telefone = malloc(sizeof(int));
        char *nome = malloc(sizeof(char) * 11);
        scanf("%10s", nome);
        printf("Digite a idade: ");
        scanf("%d", idade);
        printf("Digite o telefone: ");
        scanf("%i", telefone);
        addContato(nome, idade, telefone, pBuffer);
        printf("Contato adicionado com sucesso!\n");
        free(idade);
        free(nome);
        free(telefone);
        break;
    case 2:
        printf("Quantos contatos quer listar? ");
        int *total = malloc(sizeof(int));
        scanf("%d", total);
        list(pBuffer, total);
        printf("\n");
        free(total);
        break;
    case 3:
        printf("Digite o nome do contato a ser exibido: ");
        char *nomeBuscar = malloc(sizeof(char) * 11);
        scanf(" %s", nomeBuscar);
        procurarContato(pBuffer, nomeBuscar);
        printf("\n");
        free(nomeBuscar);
        break;
    case 4:
        printf("Digite o nome do contato a ser apagado: ");
        char *nomeBusca = malloc(sizeof(char) * 11);
        scanf(" %s", nomeBusca);
        delContato(nomeBusca, pBuffer);
        printf("Contato excluido com sucesso!\n");
        free(nomeBusca);
        break;
    case 5:
        *rodando = 1;
        freeList(pBuffer);
        break;
    default:
        printf("\nOpcao invalida\n");
        break;
    }
}
