#include <stdio.h>
#include <stdlib.h>

#define BASE 8

int main (){

    int entrada;
    int salida;

    //Imprimir requisito de entrada de datos
    printf("Introduce un número de 0 a 999: ");
    //Entrada del dato.
    scanf(" %i", &entrada);
    //Imprimir último dígito.
    salida = entrada % BASE;
    //Mover dígitos a la dcha
    entrada /= BASE;
    //Imprimir último dígito.
    salida = salida * BASE + entrada % BASE;
    //Mover dígitos a la dcha
    entrada /= BASE;
    //Imprimir último dígito.
    salida = salida * BASE + entrada % BASE;    
    printf("%i\n", salida);

    return EXIT_SUCCESS;
}
