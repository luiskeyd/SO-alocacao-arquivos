#ifndef DISCO_H
#define DISCO_H
#include "arquivo.h"

#define TAM_DISCO 50

typedef struct {
  Arquivo *arquivo;
  int ocupado;
} Bloco;

extern Bloco disco[TAM_DISCO];

void inicializarDisco();
void mostrarDisco();

#endif