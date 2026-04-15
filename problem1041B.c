#include <stdio.h>
//AlUNO: Carlos Henrique Ferreira Messias

//// Calcula o MDC entre numerador (x) e denominador (y)
long long CalcMDC(long long LarguraMax, long long AlturaMax) {
    while (AlturaMax != 0) {
        long long Aux = AlturaMax;
        AlturaMax = LarguraMax % AlturaMax;
        LarguraMax = Aux;
    }
    return LarguraMax;
}

int main() {
    long long LarguraMax, AlturaMax, numerador, denominador, NumDeTVs;
    
    scanf("%lld %lld %lld %lld", &LarguraMax,  &AlturaMax, &numerador, &denominador);

   
    long long SimplificadorMDC = CalcMDC(numerador, denominador);

    //Simplifica a razão x/y o maximo possivel
    numerador /= SimplificadorMDC;
    denominador /= SimplificadorMDC;

    //pega o minimo (numero de TVs validas)
    long long k1 = LarguraMax / numerador;
    long long k2 = AlturaMax / denominador;

   
    if(k1 < k2){
        NumDeTVs = k1;
    }
    else{
        NumDeTVs = k2;
    }

    printf("%lld\n", NumDeTVs);

    return 0;
}

