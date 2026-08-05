#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


typedef struct NoDeLI {
    double valor;
    struct NoDeLI *proximo;
} NoDeLI;


typedef struct NoDeLE {
    int chave;
    NoDeLI *head_li;
    int tamanho_li;
    struct NoDeLE *anterior;
    struct NoDeLE *proximo;
} NoDeLE;


static int ler_token(char *buf, int tamanho_max) {
    int c, j = 0;

    while ((c = getchar_unlocked()) != EOF) {
        if (c == '\n') { ungetc(c, stdin); return 0; }
        if (c != ' ' && c != '\t' && c != '\r') { buf[j++] = c; break; }
    }
    if (j == 0) return 0;
    while (j < tamanho_max - 1 && (c = getchar_unlocked()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            if (c == '\n') ungetc(c, stdin);
            break;
        }
        buf[j++] = c;
    }
    buf[j] = '\0';
    return j;
}

static void pular_linha(void) {
    int c;
    while ((c = getchar_unlocked()) != EOF && c != '\n');
}


static void inserir_li(NoDeLE *no, double valor) {
   
    if (no->head_li) {
        NoDeLI *atual = no->head_li;
        for (int i = 0; i < no->tamanho_li; i++) {
            if (fabs(atual->valor - valor) < 1e-9) return;
            atual = atual->proximo;
        }
    }

    NoDeLI *novo = malloc(sizeof(NoDeLI));
    novo->valor = valor;
    no->tamanho_li++;

    if (!no->head_li) {
        novo->proximo = novo;
        no->head_li = novo;
        return;
    }

    int tamanho = no->tamanho_li - 1;

 
    if (valor >= no->head_li->valor) {
        NoDeLI *ultimo = no->head_li;
        for (int i = 0; i < tamanho - 1; i++) ultimo = ultimo->proximo;
        novo->proximo = no->head_li;
        ultimo->proximo = novo;
        no->head_li = novo;
        return;
    }

    NoDeLI *atual = no->head_li;
    for (int i = 0; i < tamanho; i++) {
        int eh_ultimo = (atual->proximo == no->head_li);
        if (eh_ultimo || valor >= atual->proximo->valor) {
            novo->proximo = atual->proximo;
            atual->proximo = novo;
            return;
        }
        atual = atual->proximo;
    }
}


static NoDeLE *inserir_le(NoDeLE **head, int chave) {
    NoDeLE *verificacao = *head;
    while (verificacao) {
        if (verificacao->chave == chave) return NULL;
        verificacao = verificacao->proximo;
    }

    NoDeLE *novo = malloc(sizeof(NoDeLE));
    novo->chave = chave;
    novo->head_li = NULL;
    novo->tamanho_li = 0;
    novo->anterior = NULL;
    novo->proximo = NULL;

    if (!*head) { *head = novo; return novo; }

    NoDeLE *atual = *head;
    while (atual && atual->chave < chave) atual = atual->proximo;

    if (!atual) {
        NoDeLE *ultimo = *head;
        while (ultimo->proximo) ultimo = ultimo->proximo;
        ultimo->proximo = novo; novo->anterior = ultimo;
    } else if (atual == *head) {
        novo->proximo = *head; (*head)->anterior = novo; *head = novo;
    } else {
        novo->anterior = atual->anterior; novo->proximo = atual;
        atual->anterior->proximo = novo; atual->anterior = novo;
    }
    return novo;
}


static NoDeLE *buscar_le_para(NoDeLE *head, double valor) {
    NoDeLE *atual = head;
    while (atual) {
        if (fabs(valor - atual->chave) < 1.0) return atual;
        atual = atual->proximo;
    }
    return NULL;
}

static void liberar_lista_le(NoDeLE *head) {
    while (head) {
        if (head->head_li) {
            NoDeLI *inicio = head->head_li;
            NoDeLI *atual = inicio;
            int tamanho = head->tamanho_li;
            for (int i = 0; i < tamanho; i++) {
                NoDeLI *tmp = atual->proximo;
                free(atual);
                atual = tmp;
            }
        }
        NoDeLE *tmp = head->proximo;
        free(head);
        head = tmp;
    }
}


static void imprimir_double(double valor) {
    printf("%.2f", valor);
}

static void imprimir_lista(NoDeLE *head) {
    putchar_unlocked('[');
    NoDeLE *le = head;
    int primeiro = 1;
    while (le) {
        if (!primeiro) { putchar_unlocked('-'); putchar_unlocked('>'); }
        primeiro = 0;
        printf("%d", le->chave);
        if (!le->head_li) {
            putchar_unlocked('('); putchar_unlocked(')');
        } else {
            putchar_unlocked('(');
            NoDeLI *atual = le->head_li;
            for (int i = 0; i < le->tamanho_li; i++) {
                if (i > 0) { putchar_unlocked('-'); putchar_unlocked('>'); }
                imprimir_double(atual->valor);
                atual = atual->proximo;
            }
            putchar_unlocked(')');
        }
        le = le->proximo;
    }
    putchar_unlocked(']');
    putchar_unlocked('\n');
}

int main(void) {
    int n;
    scanf("%d", &n);
    pular_linha();

    char token[64];

    for (int i = 0; i < n; i++) {
        NoDeLE *head = NULL;
        int lendo_li = 0;

        while (ler_token(token, sizeof(token))) {
            if (strcmp(token, "LE") == 0) {
                lendo_li = 0;
            } else if (strcmp(token, "LI") == 0) {
                lendo_li = 1;
            } else {
                if (!lendo_li) {
                    int chave = atoi(token);
                    inserir_le(&head, chave);
                } else {
                    double valor = atof(token);
                    NoDeLE *destino = buscar_le_para(head, valor);
                    if (destino) inserir_li(destino, valor);
                }
            }
        }
        pular_linha(); 

        imprimir_lista(head);
        liberar_lista_le(head);
    }
    return 0;
}