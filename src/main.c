/*=============================================================
Arquivo cntendo a função principal interativa do sistema de
alocação de arquivos
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/disco.h"
#include "../include/arquivo.h"
#include "../include/alocacao.h"

int main() {
    printf("=============================================\n");
    printf("Bem-vindo ao sistema de alocação de arquivos!\n");
    printf("=============================================\n");
    printf("Deseja iniciar o sistema? (1 - Sim, 0 - Não): ");
    int iniciar;
    scanf("%d", &iniciar);
    if (!iniciar) {
        printf("Encerrando o sistema. Até mais!\n");
        return 0;
    }

    inicializarDisco();
    system("clear");
    mostrarDisco();
    return 0;
}