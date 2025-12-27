/*=============================================================
Arquivo de implementação dos métodos de alocação de memória
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#include <stdio.h>
#include <string.h>
#include "../include/disco.h"
#include "../include/arquivo.h"

#define TRUE 1
#define FALSE 0

  int alocacaoContigua(Bloco disco[], Arquivo *arquivo) {
    int livres = 0;
    int inicio = -1;
    
    for (int i = 0; i < TAM_DISCO; i++) { // percorre todo o disco
      if (!disco[i].ocupado) { // se o bloco estiver livre, incrementa o contador
        if (livres == 0) { // se é o primeiro bloco livre encontrado, salva o índice
          inicio = i;
        }
        livres++;
        if (livres == arquivo->tamanho) { // se encontrou espaço suficiente, aloca
          for (int j = inicio; j < arquivo->tamanho + inicio; j++) {
            disco[j].ocupado = 1;
            disco[j].arquivo = arquivo;
          }
          arquivo->blocoInicial = inicio; // basta o índice do primeiro bloco
          arquivo->tipo = CONTIGUA;
          return TRUE;
        }
      } else { // se o bloco não estiver livre, reseta o contador
        livres = 0;
      }
    }
    return FALSE;
  }

int alocacaoIndexada(Bloco disco[], Arquivo *arquivo) {
    int blocoIndice = -1;

    // Encontra um bloco livre para o índice
    for (int i = 0; i < TAM_DISCO; i++) {
        if (!disco[i].ocupado) {
            blocoIndice = i;
            disco[i].ocupado = 1;
            disco[i].arquivo = arquivo;
            break; // para após encontrar o primeiro bloco livre
        }
    }

    if (blocoIndice == -1) // não encontrou bloco livre para o índice
        return FALSE;

    int indicesOcupados = 0;

    // percorre todo o disco ou até preencher o arquivo
    for (int i = 0; i < TAM_DISCO && indicesOcupados < arquivo->tamanho; i++) {
        if (!disco[i].ocupado) { // se o bloco estiver livre, aloca
            disco[i].ocupado = 1;
            disco[i].arquivo = arquivo;
            arquivo->blocos[indicesOcupados] = i; // salva o índice do bloco alocado no bloco de dados
            indicesOcupados++;
        }
    }

    // Se não conseguiu alocar todo o arquivo, desfaz a alocação
    if (indicesOcupados < arquivo->tamanho) {
        disco[blocoIndice].ocupado = 0; // desaloca o bloco de índice
        disco[blocoIndice].arquivo = NULL;

        // desaloca os blocos de dados já alocados
        for (int j = 0; j < indicesOcupados; j++) {
            int aux = arquivo->blocos[j];
            disco[aux].ocupado = 0;
            disco[aux].arquivo = NULL;
        }
        return FALSE;
    }

    arquivo->blocoInicial = blocoIndice; // índice
    arquivo->tipo = INDEXADA;
    return TRUE;
}


int alocacaoEncadeada(Bloco disco[], Arquivo *arquivo) {
  int indicesOcupados = 0;
  int achouOprimeiro = FALSE;
  int anterior = -1;

  // Percorre todo o disco ou até preencher o arquivo
  for (int i = 0; i < TAM_DISCO && indicesOcupados < arquivo->tamanho; i++) { 
    if (!disco[i].ocupado) { // se o bloco estiver livre, aloca
      disco[i].ocupado = 1;
      disco[i].arquivo = arquivo;
      indicesOcupados++;

      // se é o primeiro bloco alocado, salva o índice e como o anterior para o próximo
      if (!achouOprimeiro) { 
        arquivo->blocoInicial = i;
        achouOprimeiro = TRUE;
        anterior = i;
      } else { // se não for o primeiro bloco,
        // liga o bloco anterior ao atual
        disco[anterior].proximo = i;
        anterior = i;
      }
    }
  }

  // Se não conseguiu alocar todo o arquivo, desfaz a alocação
  if (indicesOcupados < arquivo->tamanho) {
        int atual = arquivo->blocoInicial;

        while (atual != -1) { // percorre a lista encadeada desalocando
            int prox = disco[atual].proximo;
            disco[atual].ocupado = 0;
            disco[atual].arquivo = NULL;
            disco[atual].proximo = -1;
            atual = prox;
        }

        arquivo->blocoInicial = -1;
        return FALSE;
    }

    arquivo->tipo = ENCADEADA;
    return TRUE;
}
