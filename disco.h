#ifndef DISCO_H
#define DISCO_H
#include "arquivo.h"

#define TAM_DISCO 50

typedef struct {
  Arquivo *arquivo;
  int ocupado;
  int proximo; // só pra alocação encadeada
} Bloco;

extern Bloco disco[TAM_DISCO];

void inicializarDisco();
void mostrarDisco();

#endif