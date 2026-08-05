#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int v[100];
    int tam;
    int soma;
    int ordem;
} Lista;

void ordenarNumeros(int v[], int n) {

    int i, j, aux;

    for(i = 0; i < n - 1; i++) {

        for(j = 0; j < n - i - 1; j++) {

            if(v[j] > v[j + 1]) {

                aux = v[j];
                v[j] = v[j + 1];
                v[j + 1] = aux;
            }
        }
    }
}

void ordenarListas(Lista l[], int n) {

    int i, j;

    for(i = 0; i < n - 1; i++) {

        for(j = 0; j < n - i - 1; j++) {

            if(l[j].soma < l[j + 1].soma) {

                Lista aux = l[j];
                l[j] = l[j + 1];
                l[j + 1] = aux;
            }
        }
    }
}

int main() {

    int t;
    scanf("%d", &t);

    getchar();

    while(t--) {

        char linha[1000];

        fgets(linha, 1000, stdin);

        Lista listas[100];

        int qtd = 0;

        char *tok = strtok(linha, " \n");

        while(tok != NULL) {

            if(strcmp(tok, "start") == 0) {

                listas[qtd].tam = 0;
                listas[qtd].soma = 0;
                listas[qtd].ordem = qtd;

                tok = strtok(NULL, " \n");

                while(tok != NULL && strcmp(tok, "start") != 0) {

                    int x = atoi(tok);

                    listas[qtd].v[listas[qtd].tam++] = x;
                    listas[qtd].soma += x;

                    tok = strtok(NULL, " \n");
                }

                ordenarNumeros(listas[qtd].v, listas[qtd].tam);

                qtd++;
            }
            else {
                tok = strtok(NULL, " \n");
            }
        }

        int manter[100];

        int i, j;

        for(i = 0; i < qtd; i++)
            manter[i] = 1;

        for(i = 0; i < qtd; i++) {

            for(j = i + 1; j < qtd; j++) {

                if(listas[i].soma == listas[j].soma) {

                    manter[i] = 0;
                }
            }
        }

        Lista finais[100];
        int qtdFinal = 0;

        for(i = 0; i < qtd; i++) {

            if(manter[i]) {

                finais[qtdFinal++] = listas[i];
            }
        }

        ordenarListas(finais, qtdFinal);

        for(i = 0; i < qtdFinal; i++) {

            printf("start");

            int k;

            for(k = 0; k < finais[i].tam; k++) {

                printf(" %d", finais[i].v[k]);
            }

            if(i < qtdFinal - 1)
                printf(" ");
        }

        printf("\n");
    }

    return 0;
}

