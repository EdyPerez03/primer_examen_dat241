#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void fibonacci(int n) {
    long long* fib = (long long*)malloc(n * sizeof(long long)); // Asigna memoria dinámica
    fib[0] = 0;
    fib[1] = 1;

#pragma omp parallel
    {
#pragma omp for
        for (int i = 2; i < n; i++) {
            fib[i] = fib[i - 1] + fib[i - 2];
        }
    }

    // Imprime la serie
    printf("Serie Fibonacci:\n");
    for (int i = 0; i < n; i++) {
        printf("%lld ", fib[i]);
    }
    printf("\n");

    free(fib); // Libera la memoria asignada
}

int main() {
    int n = 10; // Cambia este valor para generar más términos
    fibonacci(n);
    return 0;
}
