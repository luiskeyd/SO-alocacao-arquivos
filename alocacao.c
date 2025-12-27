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

int alocacacaoIndexada(Bloco disco[], Arquivo *arquivo) {
  int indicesOcupados = 0;

  for (int i = 0; i < TAM_DISCO && indicesOcupados < arquivo->tamanho; i++) {
    if (!disco[i].ocupado) {
      disco[i].ocupado = 1;
      disco[i].arquivo = arquivo;
      arquivo->blocos[indicesOcupados] = i;
      indicesOcupados++;
    }
  }

  if (indicesOcupados < arquivo->tamanho) {
    for (int j = 0; j < indicesOcupados; j++) {
      int aux = arquivo->blocos[j];
      disco[aux].ocupado = 0;
      disco[j].arquivo = NULL;
    }
    return FALSE;
  }

  arquivo->tipo = INDEXADA;

  return TRUE;
}

int alocacaoEncadeada(Bloco disco[], Arquivo *arquivo) {
  int indicesOcupados = 0;
  int achouOprimeiro = FALSE;
  int anterior = -1;

  for (int i = 0; i < TAM_DISCO && indicesOcupados < arquivo->tamanho; i++) {
    if (!disco[i].ocupado) {
      disco[i].ocupado = 1;
      disco[i].arquivo = arquivo;
      indicesOcupados++;
      if (!achouOprimeiro) {
        arquivo->blocoInicial = i;
        achouOprimeiro = TRUE;
        anterior = i;
      } else {
        disco[anterior].proximo = i;
      }
    }
  }

  if (indicesOcupados < arquivo->tamanho) {
    int prox = disco[arquivo->blocoInicial].proximo;
    
    while (prox != -1) {
      disco[prox].ocupado = 0;
      disco[prox].arquivo = NULL;
      prox = disco[prox].proximo;
    }

    if (arquivo->blocoInicial != -1) {
      disco[arquivo->blocoInicial].ocupado = 0;
      disco[arquivo->blocoInicial].arquivo = NULL;
      arquivo->blocoInicial = -1;
    }
    
    return FALSE;
  }

  return TRUE;
}
