#include <stdio.h>
#include "disco.h"

Bloco disco[TAM_DISCO];

void inicializarDisco() {
  for (int i = 0; i < TAM_DISCO; i++) {
    disco[i].ocupado = 0;   // Marcando todo bloco como livre
    disco[i].proximo = -1; // aponta pra -1 pq começa sem apontar pra nada
    disco[i].arquivo->nome = ' ';
  }
}

void mostrarDisco() {
  printf("\nDisco\n");
  for (int i = 0; i < TAM_DISCO; i++) {
    if (disco[i].ocupado) {
      printf("[Arquivo]");
    } else {
      printf("[Livre]");
    }
  }
  printf("\n");
}
