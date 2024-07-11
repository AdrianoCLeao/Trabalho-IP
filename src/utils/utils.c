#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lerString(char **string, char *textoInput) {
    char buffer[500];

    setbuf(stdin, NULL);
    printf("%s: ", textoInput);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    *string = malloc(strlen(buffer) * sizeof(char)); 
    strcpy(*string, buffer);
}