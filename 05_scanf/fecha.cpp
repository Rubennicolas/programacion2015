#include <stdio.h>
#include <stdlib.h>

int main (){
    int mes, anio;

    const char *MES[12] = {
        "Enero", "Febrero", "Marzo", "Abril", "Mayo",
        "Junio", "Julio", "Agosto", "Septiembre",
        "Octubre", "Noviembre", "Diciembre"
    };

    printf("Fecha de nacimiento (dd/mm/aa): ");
    scanf(" %*i/%i/%i", &mes, &anio);
    //El * es el caracter de supresión de asignación.

    printf("Naciste en el mes %s del año %i.\n", MES[mes-1], anio);

    return EXIT_SUCCESS;
}

