#include <stdio.h>
//ALUNO: Carlos Henrique Ferreira Messias
int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int iCont;
        int jCont;
        int n;
        scanf("%d", &n);
        
        int a[n];
        int freq[n + 1];
        
        for (iCont = 1; iCont <= n; iCont++) {
            freq[iCont] = 0;
        }
        
        int repetido = 0;
        
        for (iCont = 0; iCont < n; iCont++) {
            scanf("%d", &a[iCont]);
            freq[a[iCont]]++;
            if (freq[a[iCont]] > 1) {
                repetido = 1;
            }
        }
        
        // Se tem repetido, sempre YES
        if (repetido) {
            printf("YES\n");
            continue;
        }
        
        // Se não tem repetido, é permutação
        // Preciso contar os ciclos
        
        int vis[n + 1];
        for (iCont = 1; iCont <= n; iCont++) {
            vis[iCont] = 0;
        }
        
        int ciclos = 0;
        for (int iCont = 1; iCont <= n; iCont++) {
            if (!vis[iCont]) {
                ciclos++;
                jCont = iCont;
                while (!vis[jCont]) {
                    vis[jCont] = 1;
                    jCont = a[jCont - 1];
                }
            }
        }
        
        // (n - ciclos) precisa ser par
        if ((n - ciclos) % 2 == 0) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}