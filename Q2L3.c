#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define TAM 20

typedef struct No
{
    int chave;
    struct No *esq;
    struct No *dir;
    struct No *mae;
} No;

typedef struct Arvore
{
    No *raiz;
} Arvore;

No *criar_no(int chave)
{
    No *novo = malloc(sizeof(No));
    novo->chave = chave;
    novo->dir = novo->esq = novo->mae = NULL;
    return novo;
}

Arvore * criar_arvore()
{
    Arvore *nova = malloc(sizeof(Arvore));
    nova->raiz = NULL;
    return nova;
}


void inserir_no(No *novo, Arvore *arvore)
{
    if (arvore->raiz == NULL)
    {
        arvore->raiz = novo;
    }
    else
    {
        No *c3po = arvore->raiz;
        No *luke_skywalker = c3po;
        while (c3po != NULL)
        {
            luke_skywalker = c3po;
            if (novo->chave < c3po->chave)
            {
                c3po = c3po->esq;
            }
            else
            {
                c3po = c3po->dir;
            }
        }
        if (novo->chave < luke_skywalker->chave)
        {
            luke_skywalker->esq = novo;
        }
        else
        {
            luke_skywalker->dir = novo;
        }
        novo->mae = luke_skywalker;
    }
}

void imprimir_arvore(No * no, int i){
    if(no!=NULL){
        imprimir_arvore(no->esq, i+1);
        printf(" (%d) \n",no->chave);
        imprimir_arvore(no->dir, i+1);
    }
}

int SomaEsquerda(No * raiz){
    No * y = raiz;
    int EsqSum = 0;

    while(y!=NULL && y->esq!=NULL){
        y=y->esq;
        EsqSum += y->chave;
    }
    return EsqSum;
}

int SomaDireita(No * raiz){
    No * y = raiz;
    int DirSum = 0;

    while(y!=NULL && y->esq!=NULL){
        y=y->esq;
        DirSum += y->chave;
    }
    return DirSum;
}

// nesse caso sabemos que X tem dois filhos
// essa função é parcial
No * sucessor_arvore(No * x){
    assert(x->dir!=NULL);
    //No * y = x->dir;
    return minimo(x->dir);// y
}

void deletarArvore(struct No** raizRef) {
    // Caso base: se a árvore ou o nó atual estiver vazio, não faz nada
    if (raizRef == NULL || *raizRef == NULL) {
        return;
    }

    struct No* atual = *raizRef;

    // 1. Primeiro, deleta recursivamente a subárvore esquerda
    deletarArvore(&(atual->esq));

    // 2. Depois, deleta recursivamente a subárvore direita
    deletarArvore(&(atual->dir));

    // 3. Por fim, deleta o próprio nó atual (a raiz local)
    // printf("Deletando no com valor: %d\n", atual->dado); // Opcional: para depuração
    free(atual);

    // Garante que o ponteiro que apontava para este nó agora aponte para NULL
    *raizRef = NULL;
}

int main()
{
    int qtdVezes;
    char Str[5000], StrCopy[5000], StrSaida[5000] = "";

    scanf("%i", &qtdVezes);

    for(int i = 0; i < qtdVezes; i++){

        Arvore * arvore = criar_arvore();
        int chave;

        scanf("%[^/n]", Str);
        strcpy(StrCopy, Str);

        char * token = strtok(StrCopy, " ");

        while(token != NULL){
            chave = token - '0';
            inserir_no(criar_no(chave),arvore);
            token = strtok(NULL, " ");
        };

        while(token != NULL){
            No * NoAtual = arvore->raiz;
            int SumEsq;
            int SumDir;

            strcat(StrSaida, token);

            SumEsq = SomaEsquerda(NoAtual);
            SumDir = SomaDireita(NoAtual);
        };

        deletarArvore(arvore);
        free(arvore);
    };

    return EXIT_SUCCESS;
}