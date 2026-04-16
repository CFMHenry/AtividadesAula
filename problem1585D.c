#include <stdio.h>

// ALUNO: Carlos Henrique Ferreira Messias

int main() {
    int quantidadeTestes;
    scanf("%d", &quantidadeTestes);
    
    while (quantidadeTestes--) {
        int tamanhoArray;
        scanf("%d", &tamanhoArray);
        
        int array[tamanhoArray];
        int frequencia[tamanhoArray + 1];
        
        for (int indice = 1; indice <= tamanhoArray; indice++) {
            frequencia[indice] = 0;
        }
        
        int existeRepetido = 0;
        
        for (int indice = 0; indice < tamanhoArray; indice++) {
            scanf("%d", &array[indice]);
            frequencia[array[indice]]++;
            
            if (frequencia[array[indice]] > 1) {
                existeRepetido = 1;
            }
        }
        
        if (existeRepetido) {
            printf("YES\n");
            continue;
        }
        
        int visitado[tamanhoArray + 1];
        for (int indice = 1; indice <= tamanhoArray; indice++) {
            visitado[indice] = 0;
        }
        
        int quantidadeCiclos = 0;
        
        for (int inicio = 1; inicio <= tamanhoArray; inicio++) {
            if (!visitado[inicio]) {
                quantidadeCiclos++;
                
                int atual = inicio;
                while (!visitado[atual]) {
                    visitado[atual] = 1;
                    atual = array[atual - 1];
                }
            }
        }
        
        int numeroTrocas = tamanhoArray - quantidadeCiclos;
        
        if (numeroTrocas % 2 == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}
