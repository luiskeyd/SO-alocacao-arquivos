/*=============================================================
Arquivo de implementação da criação e inicialização do arquivo
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#include <stdio.h>
#include "arquivo.h"

Arquivo *inicializarArquivo(char nome, int tamanho, TipoAlocacao tipo) {
  Arquivo *arquivo;

  arquivo->nome = nome;
  arquivo->tamanho = tamanho;
  arquivo->tipo = tipo;
  arquivo->blocoInicial = -1;
  
  for (int i = 0; i < MAX_ARQUIVOS; i++) {
    arquivo->blocos[i] = -1;
  }

  return arquivo;
}
