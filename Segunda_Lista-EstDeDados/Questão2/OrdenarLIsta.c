#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int *valor;
    int SomaValor;
    char *str;
    struct no *next;
}No;

void inserir_no_fim(No **lista){
    No *aux, *novo = malloc(sizeof(No));
    if(novo){
        novo->next = NULL;

        // é o primeiro?

        if(*lista == NULL)
            *lista = novo;
        else{
            aux = *lista;
            while(aux->next){
                aux = aux->next;
            }
            aux->next = novo;
        }
    }
}

void inserir_num(int num){

}


int main(){
    No *lista = NULL;
    char linha[256];

    fgets(linha, 256, stdin);

    char *token;

    token = strtok(linha, " ");

    while(token != NULL)
    {
        if(strcmp(token, "start") != 0)
        {
            numero = atoi(token);

            vetor[indice] = numero;

            indice++;
        }

        token = strtok(NULL, " ");
    }
}