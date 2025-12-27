/*=============================================================
Arquivo de especificação da estrutura do disco e suas funções
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#ifndef DISCO_H
#define DISCO_H
#include "arquivo.h"

#define TAM_DISCO 50  // Tamanho total do disco em blocos

typedef struct {
  Arquivo *arquivo; // ponteiro para o arquivo alocado no bloco
  int ocupado; // 0 para livre, 1 para ocupado
  int proximo; // só pra alocação encadeada
} Bloco;

extern Bloco disco[TAM_DISCO];

void inicializarDisco(); // Inicializa o disco, marcando todos os blocos como livres
void mostrarDisco(); // Mostra o estado atual do disco

#endif