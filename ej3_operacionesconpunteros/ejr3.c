#include <stdio.h>

void suma(int *a, int *b, int *resultado) {
    *resultado = *a + *b;
}

void resta(int *a, int *b, int *resultado) {
    *resultado = *a - *b;
}

void multiplicacion(int *a, int *b, int *resultado) {
    *resultado = *a * *b;
}

void division(int *a, int *b, float *resultado) {
    if (*b != 0)
        *resultado = (float)(*a) / *b;
    else
        printf("Error: Division por cero\n");
}

int main() {


    int a, b, res;
    float div_res;
    printf("Programa en C con punteros (suma, resta, multiplicacion, division)\n");
    printf("Introduce el primer numero: ");
    scanf("%d", &a);
    printf("Introduce el segundo numero: ");
    scanf("%d", &b);


    suma(&a, &b, &res);
    printf("Suma: %d\n", res);

    resta(&a, &b, &res);
    printf("Resta: %d\n", res);

    multiplicacion(&a, &b, &res);
    printf("Multiplicacion: %d\n", res);

    division(&a, &b, &div_res);
    printf("Division: %.2f\n", div_res);

    return 0;
}
