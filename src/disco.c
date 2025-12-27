/*=============================================================
Arquivo de implementação ds funções do disco
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#include <stdio.h>
#include "../include/disco.h"

Bloco disco[TAM_DISCO];

void inicializarDisco() {
  for (int i = 0; i < TAM_DISCO; i++) {
    disco[i].ocupado = 0;   // Marcando todo bloco como livre
    disco[i].proximo = -1; // aponta pra -1 pq começa sem apontar pra nada
    disco[i].arquivo = NULL; // nenhum arquivo alocado
  }
}

void mostrarDisco() {
  int cont = 0;
  printf("Estado do Disco:\n");
  for (int i = 0; i < TAM_DISCO; i++) {
    if (disco[i].ocupado && disco[i].arquivo != NULL) {
      printf("[%c]\t", disco[i].arquivo->nome);
    } else {
      printf("[ ]\t");
    }
    cont++;
    if (cont == 10) {
      printf("\n");
      cont = 0;
    }
  }
  printf("\n");
}

