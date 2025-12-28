/*=============================================================
Arquivo de implementação da criação e inicialização do arquivo
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#include <stdio.h>
#include <stdlib.h>
#include "../include/arquivo.h"

// Alocação de um arquivo 
Arquivo *inicializarArquivo(char nome, int tamanho, TipoAlocacao tipo) {
  Arquivo *arquivo = (Arquivo *) malloc(sizeof(Arquivo));

  if (arquivo == NULL) {
    return NULL; // Falha de alocação
  }

  arquivo->nome = nome;
  arquivo->tamanho = tamanho;
  arquivo->tipo = tipo;
  arquivo->blocoInicial = -1;

  for (int i = 0; i < MAX_ARQUIVOS; i++) {
    arquivo->blocos[i] = -1;
  }

  return arquivo;
}