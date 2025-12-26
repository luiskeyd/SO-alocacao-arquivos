#include <stdio.h>
#include <string.h>
#include "disco.h"
#include "arquivo.h"

#define TRUE 1
#define FALSE 0

int alocacaoContigua(Bloco disco[], Arquivo *arquivo) {
  int livres = 0;
  int inicio = -1;
  
  for (int i = 0; i < TAM_DISCO; i++) {
    if (!disco[i].ocupado) {
      if (livres == 0) {
        inicio = i;
      }
      livres++;
      if (livres == arquivo->tamanho) {
        for (int j = inicio; j < arquivo->tamanho + inicio; j++) {
          disco[j].ocupado = 1;
          disco[j].arquivo = arquivo;
        }
        arquivo->blocoInicial = inicio;
        arquivo->tipo = CONTIGUA;
        return TRUE;
      }
    } else {
      livres = 0;
    }
  }
  return FALSE;
}
