#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ---------- Pool de nos (array dinamico, sem malloc por no) ---------- */
typedef struct {
    long chave;
    int esq, dir, pai; /* indices no pool; -1 = NULL */
} No;

static No *pool = NULL;
static size_t poolCap = 0;
static size_t poolSize = 0;

static void pool_reservar(size_t minCap) {
    if (minCap <= poolCap) return;
    size_t novaCap = poolCap ? poolCap * 2 : 4096;
    while (novaCap < minCap) novaCap *= 2;
    No *tmp = realloc(pool, novaCap * sizeof(No));
    if (!tmp) { fprintf(stderr, "sem memoria\n"); exit(1); }
    pool = tmp;
    poolCap = novaCap;
}

static int cria_no(long chave) {
    pool_reservar(poolSize + 1);
    int idx = (int)poolSize++;
    pool[idx].chave = chave;
    pool[idx].esq = pool[idx].dir = pool[idx].pai = -1;
    return idx;
}

/* Insere e devolve (via *altura) o nivel (profundidade) do no inserido.
   Chave >= no atual sempre vai para a direita (regra do enunciado). */
static int insere(int *raiz, long chave, int *altura) {
    int novo = cria_no(chave);
    if (*raiz == -1) { *raiz = novo; *altura = 0; return novo; }
    int atual = *raiz, nivel = 0;
    for (;;) {
        nivel++;
        if (chave < pool[atual].chave) {
            if (pool[atual].esq == -1) { pool[atual].esq = novo; pool[novo].pai = atual; break; }
            atual = pool[atual].esq;
        } else {
            if (pool[atual].dir == -1) { pool[atual].dir = novo; pool[novo].pai = atual; break; }
            atual = pool[atual].dir;
        }
    }
    *altura = nivel;
    return novo;
}

/* Predecessor estrutural (in-order) do no `no`. Retorna 1 e preenche *valor,
   ou 0 se nao existir (no e o minimo da arvore). */
static int predecessor(int no, long *valor) {
    if (pool[no].esq != -1) {
        int atual = pool[no].esq;
        while (pool[atual].dir != -1) atual = pool[atual].dir;
        *valor = pool[atual].chave;
        return 1;
    }
    int atual = no, pai = pool[no].pai;
    while (pai != -1 && atual == pool[pai].esq) { atual = pai; pai = pool[pai].pai; }
    if (pai == -1) return 0;
    *valor = pool[pai].chave;
    return 1;
}

/* ---------- Leitura rapida e sem limite de tamanho de linha ---------- */

/* Le uma linha inteira (sem limite fixo), devolve -1 em EOF sem dados.
   `buf`/`cap` sao mantidos entre chamadas (estilo getline). */
static long ler_linha(char **buf, size_t *cap, FILE *f) {
    size_t n = getline(buf, cap, f);
    return n; /* getline inclui o '\n' se existir; retorna -1 em EOF */
}

/* Parser manual de inteiros (evita overhead do strtok/atol).
   Avanca *p ate o proximo numero; retorna 1 se achou um numero em *out. */
static int proximo_inteiro(char **p, long *out) {
    char *s = *p;
    while (*s && (*s == ' ' || *s == '\t' || *s == '\r' || *s == '\n')) s++;
    if (*s == '\0') return 0;
    int neg = 0;
    if (*s == '-') { neg = 1; s++; } /* defensivo, mesmo o enunciado falando em naturais */
    if (*s < '0' || *s > '9') return 0;
    long v = 0;
    while (*s >= '0' && *s <= '9') { v = v * 10 + (*s - '0'); s++; }
    *out = neg ? -v : v;
    *p = s;
    return 1;
}

/* ---------- Saida bufferizada e dinamica ---------- */
static char *outbuf = NULL;
static size_t outcap = 0, outpos = 0;

static void out_reservar(size_t extra) {
    if (outpos + extra <= outcap) return;
    size_t novaCap = outcap ? outcap * 2 : (1 << 20);
    while (novaCap < outpos + extra) novaCap *= 2;
    char *tmp = realloc(outbuf, novaCap);
    if (!tmp) { fprintf(stderr, "sem memoria\n"); exit(1); }
    outbuf = tmp;
    outcap = novaCap;
}

static void out_int(long v) {
    out_reservar(24);
    outpos += sprintf(outbuf + outpos, "%ld", v);
}
static void out_char(char c) {
    out_reservar(2);
    outbuf[outpos++] = c;
}
static void out_str(const char *s) {
    size_t len = strlen(s);
    out_reservar(len + 1);
    memcpy(outbuf + outpos, s, len);
    outpos += len;
}

int main(void) {
    char *linha = NULL;
    size_t linhaCap = 0;

    if (ler_linha(&linha, &linhaCap, stdin) < 0) return 0;
    int quantidadeLinhas = atoi(linha);

    for (int i = 0; i < quantidadeLinhas; i++) {
        if (ler_linha(&linha, &linhaCap, stdin) < 0) break;

        poolSize = 0; /* reseta o "pool" para a nova arvore (reaproveita memoria) */
        int raiz = -1;
        int noMaximoIdx = -1;
        int alturaArvore = 0;
        int primeiro = 1;

        char *p = linha;
        long chave;
        while (proximo_inteiro(&p, &chave)) {
            int alturaNo;
            int idx = insere(&raiz, chave, &alturaNo);

            if (!primeiro) out_char(' ');
            out_int(alturaNo);
            primeiro = 0;

            if (alturaNo > alturaArvore) alturaArvore = alturaNo;
            if (noMaximoIdx == -1 || chave >= pool[noMaximoIdx].chave) noMaximoIdx = idx;
        }

        if (raiz == -1) {
            /* linha sem nenhum numero valido: nao deveria ocorrer segundo o
               enunciado, mas evita comportamento indefinido */
            out_char('\n');
            fwrite(outbuf, 1, outpos, stdout);
            fflush(stdout);
            outpos = 0;
            continue;
        }

        long pred;
        int temPred = predecessor(noMaximoIdx, &pred);

        out_str(" max ");
        out_int(pool[noMaximoIdx].chave);
        out_str(" alt ");
        out_int(alturaArvore);
        out_str(" pred ");
        if (temPred) out_int(pred); else out_str("NaN");
        out_char('\n');

    
        fwrite(outbuf, 1, outpos, stdout);
        fflush(stdout);
        outpos = 0;
    }

    free(linha);
    free(pool);
    free(outbuf);
    return 0;
}