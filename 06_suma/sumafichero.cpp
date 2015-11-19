#include <stdio.h>
#include <stdlib.h>

int main (){

    int resultado = 0;
    int entrada;
    FILE *pf;

    pf = fopen("numeros.txt", "r")
    fscanf(pf, " %i", &entrada);
    resultado += entrada;
    fclose(pf);


    printfe("%i\n", resultado);


    return EXIT_SUCCESS;
}

