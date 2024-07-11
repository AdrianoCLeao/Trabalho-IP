#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* lerString(char *textoInput) {
    char buffer[500];
    char *string;

    setbuf(stdin, NULL);
    printf("%s: ", textoInput);
    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    string = malloc(strlen(buffer) * sizeof(char)); 
    strcpy(string, buffer);
    return string;
}