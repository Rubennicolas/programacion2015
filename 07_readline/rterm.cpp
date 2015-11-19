#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main (int argc, const char **argv){

    char *linea;

    system("toilet -f pagga --gay 'Remote Computer'");
    printf("Hack me if u can. \n\n\n");

    linea = readline ("Login: ");
    printf("%s ins't a valid password.\n", linea);
    linea = readline ("Login: ");
    printf("%s ins't a valid password.\n", linea);
    linea = readline ("Login: ");
    printf("%s ins't a valid password.\n", linea);

    free(linea);

    return EXIT_SUCCESS;
}

