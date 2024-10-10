#include <stdio.h>

void calcular_pi_iterativo(int iteraciones, double *pi) {
    *pi = 0.0;
    for (int i = 0; i < iteraciones; i++) {
        double term = (i % 2 == 0) ? 1.0 : -1.0;
        *pi += term / (2 * i + 1);
    }
    *pi *= 4;
}

double calcular_pi_recursivo(int i, int iteraciones) {
    if (i >= iteraciones) {
        return 0.0;
    }
    double term = (i % 2 == 0) ? 1.0 : -1.0;
    return term / (2 * i + 1) + calcular_pi_recursivo(i + 1, iteraciones);
}

int main() {
    printf("Calculo de Pi SECUENCIAL CON PUNTEROS (Iterativo)\n");
    
    int iteraciones = 10000;  
    double pi_iterativo;
    
    calcular_pi_iterativo(iteraciones, &pi_iterativo); 
    printf("Pi (iterativo): %.15f\n", pi_iterativo);

    printf("Calculo de Pi SECUENCIAL CON PUNTEROS (Recursivo)\n");
    
    double pi_recursivo = calcular_pi_recursivo(0, iteraciones) * 4; 
    printf("Pi (recursivo): %.15f\n", pi_recursivo);
    
    return 0;
}
