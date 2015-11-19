#include <stdlib.h>
#include <stdio.h>

int main(){
  
    int numero = 0;

    printf("Introduce número decimal: ");
    scanf(" %d", &numero);

    printf("%d en Hexadecimal es: %X , y en octal es: %o \n", numero, numero, numero);

    return EXIT_SUCCESS;

}
