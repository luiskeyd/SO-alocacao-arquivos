/*=============================================================
Arquivo de implementação ds funções do disco
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/disco.h"

Bloco disco[TAM_DISCO];

void inicializarDisco() {
  for (int i = 0; i < TAM_DISCO; i++) {
    disco[i].ocupado = 0;   // Marcando todo bloco como livre
    disco[i].proximo = -1; // Aponta pra -1 (nada)
    disco[i].arquivo = NULL; // Nenhum arquivo alocado
  }
}

int isEmpty(Bloco disco[]) {
    for (int i = 0; i < TAM_DISCO; i++) {
        if (disco[i].ocupado) {
            return 0; // Disco não está vazio
        }
    }
    return 1; // Disco está vazio
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

Arquivo *buscarArquivo(Bloco disco[], char nome) {
  for (int i = 0; i < TAM_DISCO; i++) {
    if (disco[i].ocupado && disco[i].arquivo != NULL && disco[i].arquivo->nome == nome) {
      return disco[i].arquivo;
    }
  }
  return NULL; // Arquivo não encontrado
}