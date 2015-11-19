#include <stdio.h>
#include <stdlib.h>

#define BASE 10

int main (){

    int entrada;

    //Imprimir requisito de entrada de datos
    printf("Introduce un número de 0 a 999: ");
    //Entrada del dato.
    scanf(" %d", &entrada);
    //Imprimir último dígito.
    printf("%d", entrada % BASE);
    //Mover dígitos a la dcha
    entrada /= BASE;
    //Imprimir último dígito.
    printf("%d", entrada % BASE);
    //Mover dígitos a la dcha
    entrada /= BASE;
    //Imprimir último dígito.
    printf("%d", entrada % BASE);
    printf("\n");

    return EXIT_SUCCESS;
}

