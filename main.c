#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#include "src/utils/utils.h"
#include "src/jogos/jogos.h"
#include "src/clientes/clientes.h"

// C:\MinGW\bin\gcc.exe -Wall -Wextra -g3 c:\Users\Desktop\Desktop\TrabalhoIP\main.c C:\Users\Desktop\Desktop\TrabalhoIP\src\jogos\jogos.c C:\Users\Desktop\Desktop\TrabalhoIP\src\utils\utils.c 

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");

    menu();

    return 0;
}