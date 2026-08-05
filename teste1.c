
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
typedef struct No {
    long chave;
    struct No *esq, *dir, *pai;
} No;
 
No* cria_no(long chave) {
    No* novo = malloc(sizeof(No));
    novo->chave = chave;
    novo->esq = novo->dir = novo->pai = NULL;
    return novo;
}
 

No* insere(No** raiz, long chave, int* altura) {
    No* novo = cria_no(chave);
    if (*raiz == NULL) {
        *raiz = novo;
        *altura = 0;
        return novo;
    }
    No* atual = *raiz;
    int nivel = 0;
    while (1) {
        nivel++;
        if (chave < atual->chave) {
            if (atual->esq == NULL) { atual->esq = novo; novo->pai = atual; break; }
            atual = atual->esq;
        } else {
            if (atual->dir == NULL) { atual->dir = novo; novo->pai = atual; break; }
            atual = atual->dir;
        }
    }
    *altura = nivel;
    return novo;
}
 
int predecessor(No* no, long* valorPredecessor) {
    if (no->esq != NULL) {
        No* atual = no->esq;
        while (atual->dir != NULL) atual = atual->dir;
        *valorPredecessor = atual->chave;
        return 1;
    }
    No* atual = no;
    No* pai = no->pai;
    while (pai != NULL && atual == pai->esq) {
        atual = pai;
        pai = pai->pai;
    }
    if (pai == NULL) return 0;
    *valorPredecessor = pai->chave;
    return 1;
}
 
void liberaArvore(No* no) {
    if (!no) return;
    liberaArvore(no->esq);
    liberaArvore(no->dir);
    free(no);
}
 
#define LINHA_MAX 10000000
 
int main(void) {
    static char linha[LINHA_MAX];
    if (!fgets(linha, LINHA_MAX, stdin)) return 0;
    int quantidadeLinhas = atoi(linha);
 
    for (int i = 0; i < quantidadeLinhas; i++) {
        if (!fgets(linha, LINHA_MAX, stdin)) break;
 
        No* raiz = NULL;
        No* noMaximo = NULL;
        int alturaArvore = 0;
        int primeiroToken = 1;
 
        char* token = strtok(linha, " \t\r\n");
        while (token != NULL) {
            long chaveAtual = atol(token);
            int alturaNo;
            No* noInserido = insere(&raiz, chaveAtual, &alturaNo);
 
            if (!primeiroToken) printf(" ");
            printf("%d", alturaNo);
            primeiroToken = 0;
 
            if (alturaNo > alturaArvore) alturaArvore = alturaNo;
            if (noMaximo == NULL || chaveAtual >= noMaximo->chave) noMaximo = noInserido;
 
            token = strtok(NULL, " \t\r\n");
        }
 
        long valorPredecessor;
        int temPredecessor = predecessor(noMaximo, &valorPredecessor);
 
        if (temPredecessor)
            printf(" max %ld alt %d pred %ld\n", noMaximo->chave, alturaArvore, valorPredecessor);
        else
            printf(" max %ld alt %d pred NaN\n", noMaximo->chave, alturaArvore);
 
        liberaArvore(raiz);
    }
    return 0;
}