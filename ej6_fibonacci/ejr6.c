#include <stdio.h>

void fibonacci(int n) {
    int a = 0, b = 1, siguiente;

    printf("Serie Fibonacci: %d %d ", a, b);

    for (int i = 2; i < n; i++) {
        siguiente = a + b;
        printf("%d ", siguiente);
        a = b;
        b = siguiente;
    }
    printf("\n");
}

int main() {
    int n = 10;  
    fibonacci(n);
    return 0;
}
