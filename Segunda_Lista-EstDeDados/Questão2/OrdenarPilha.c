#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pilha{
    char str[100][1000];
    char strFinal[10000];
    int tam;
    int topo;
} Pilha;

int estaVazia(Pilha * pilha){
    return pilha->topo == -1;
}

int estaCheia(Pilha * pilha){
    return pilha->topo == pilha->tam - 1;
}


Pilha * criarpilha(int tam){
    Pilha *nova_pilha = malloc(sizeof(Pilha));
    nova_pilha->tam = tam;
    nova_pilha->strFinal[0] = '\0';
    nova_pilha->topo = -1;

    return nova_pilha;
}

void push(Pilha * pilha, char * str){
    if(!estaCheia(pilha)){
        pilha->topo += 1;
        strncpy(pilha->str[pilha->topo], str, 999);
        pilha->str[pilha->topo][999] = '\0';
        if(strlen(pilha->strFinal) > 0) 
            strcat(pilha->strFinal, " ");
        strcat(pilha->strFinal, "push-");
        strcat(pilha->strFinal, str);
    }
}

int pop(Pilha * pilha, char strAux[][1000], int qtdPop, int topo){
    if(!estaVazia(pilha)){
        strncpy(strAux[topo], pilha->str[pilha->topo], 999);
        strAux[topo][999] = '\0';
        pilha->topo = pilha->topo - 1;
        qtdPop++;
    }

    return qtdPop;
}

int main(){
    int qtdLinhas, iCont = 0, ContTam, topoAux = -1;
    int qtdPop = 0;
    char strAux[1000], strAuxCpy[1000], PilhaAux[100][1000], NumDePOP[20], *token;

    scanf("%d", &qtdLinhas);
    getchar();

    while(iCont < qtdLinhas){
        fgets(strAux, 1000, stdin);
        strAux[strcspn(strAux, "\n")] = '\0';
        strcpy(strAuxCpy, strAux);
        token = strtok(strAuxCpy, " ");

        for(ContTam = 0; token != NULL; token = strtok(NULL, " "), ContTam++);
        Pilha * Nomes = criarpilha(ContTam);

        token = strtok(strAux, " ");

        while(token != NULL){
            topoAux = -1;
            qtdPop = 0;
            if(estaVazia(Nomes) || (strcmp(Nomes->str[Nomes->topo], token) <= 0)){
                push(Nomes, token);
             }
            else{
                while(!estaVazia(Nomes) && strcmp(Nomes->str[Nomes->topo], token) > 0){
                    topoAux++;
                    qtdPop = pop(Nomes, PilhaAux, qtdPop, topoAux);
                }

                if(strlen(Nomes->strFinal) > 0)
                    strcat(Nomes->strFinal, " ");
                sprintf(NumDePOP, "%dx-pop", qtdPop);
                strcat(Nomes->strFinal, NumDePOP);
                

                push(Nomes, token);
                
                while(qtdPop > 0){
                    push(Nomes, PilhaAux[topoAux]);
                    topoAux -= 1;
                    qtdPop--;
                }
                
                qtdPop = 0;
            }

            token = strtok(NULL, " ");
        }
        iCont++;
        printf("%s\n", Nomes->strFinal);
        free(Nomes);
    }
}






















