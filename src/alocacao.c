/*=============================================================
Arquivo de implementação dos métodos de alocação de memória
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueias, Glezier Montalvane.
Data: Dezembro de 2025
===============================================================*/

#include <stdio.h>
#include <string.h>
#include "../include/disco.h"
#include "../include/arquivo.h"

#define TRUE 1
#define FALSE 0

// Alocação contígua
int alocacaoContigua(Bloco disco[], Arquivo *arquivo) {
  int livres = 0;
  int inicio = -1;
  
  for (int i = 0; i < TAM_DISCO; i++) { // Percorre todo o disco
    if (!disco[i].ocupado) { // Se o bloco estiver livre, incrementa o contador
      if (livres == 0) { // Se é o primeiro bloco livre encontrado, salva o índice
        inicio = i;
      }
      livres++;
      if (livres == arquivo->tamanho) { // Se encontrou espaço suficiente, aloca
        for (int j = inicio; j < arquivo->tamanho + inicio; j++) {
          disco[j].ocupado = 1;
          disco[j].arquivo = arquivo;
        }
        arquivo->blocoInicial = inicio; // Basta o índice do primeiro bloco
        arquivo->tipo = CONTIGUA;
        return TRUE;
      }
    } else { // Se o bloco não estiver livre, reseta o contador
      livres = 0;
    }
  }
  return FALSE;
}

// Alocação indexada
int alocacaoIndexada(Bloco disco[], Arquivo *arquivo) {
    int blocoIndice = -1;

    // Encontra um bloco livre para o índice
    for (int i = 0; i < TAM_DISCO; i++) {
        if (!disco[i].ocupado) {
            blocoIndice = i;
            disco[i].ocupado = 1;
            disco[i].arquivo = arquivo;
            break; // Para após encontrar o primeiro bloco livre
        }
    }

    if (blocoIndice == -1) // Não encontrou bloco livre para o índice
        return FALSE;

    int indicesOcupados = 0;

    // Percorre todo o disco ou até preencher o arquivo
    for (int i = 0; i < TAM_DISCO && indicesOcupados < arquivo->tamanho; i++) {
        if (!disco[i].ocupado) { // Se o bloco estiver livre, aloca
            disco[i].ocupado = 1;
            disco[i].arquivo = arquivo;
            arquivo->blocos[indicesOcupados] = i; // Salva o índice do bloco alocado no bloco de dados
            indicesOcupados++;
        }
    }

    // Se não conseguiu alocar todo o arquivo, desfaz a alocação
    if (indicesOcupados < arquivo->tamanho) {
        disco[blocoIndice].ocupado = 0; // Desaloca o bloco de índice
        disco[blocoIndice].arquivo = NULL;

        // Desaloca os blocos de dados já alocados
        for (int j = 0; j < indicesOcupados; j++) {
            int aux = arquivo->blocos[j];
            disco[aux].ocupado = 0;
            disco[aux].arquivo = NULL;
        }
        return FALSE;
    }

    arquivo->blocoInicial = blocoIndice; // Índice
    arquivo->tipo = INDEXADA;
    return TRUE;
}

// Alocação encadeada
int alocacaoEncadeada(Bloco disco[], Arquivo *arquivo) {
int indicesOcupados = 0;
int achouOprimeiro = FALSE;
int anterior = -1;

// Percorre todo o disco ou até preencher o arquivo
for (int i = 0; i < TAM_DISCO && indicesOcupados < arquivo->tamanho; i++) { 
  if (!disco[i].ocupado) { // Se o bloco estiver livre, aloca
    disco[i].ocupado = 1;
    disco[i].arquivo = arquivo;
    indicesOcupados++;

    // Se é o primeiro bloco alocado, salva o índice e como o anterior para o próximo
    if (!achouOprimeiro) { 
      arquivo->blocoInicial = i;
      achouOprimeiro = TRUE;
      anterior = i;
    } else { // Se não for o primeiro bloco,
      // Liga o bloco anterior ao atual
      disco[anterior].proximo = i;
      anterior = i;
    }
  }
}

// Se não conseguiu alocar todo o arquivo, desfaz a alocação
if (indicesOcupados < arquivo->tamanho) {
      int atual = arquivo->blocoInicial;

      while (atual != -1) { // Percorre a lista encadeada desalocando
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

// Remoção de arquivos do disco, considerando o tipo de alocação
int removerArquivo(Bloco disco[], Arquivo *arquivo) {

  // Verifica se o arquivo é válido e se está alocado
  if (arquivo == NULL || arquivo->blocoInicial == -1) {
    return FALSE;
  }

  switch (arquivo->tipo) {

    // Alocação do arquivo de forma contígua
    case CONTIGUA: {
      // Libera todos os blocos sequenciais ocupados pelo arquivo,
      // iniciando no bloco inicial e seguindo pelo tamanho do arquivo
      for (int i = arquivo->blocoInicial;
           i < arquivo->blocoInicial + arquivo->tamanho;
           i++) {
        disco[i].ocupado = 0;
        disco[i].arquivo = NULL;
      }
      break;
    }

    // Alocação do arquivo de forma encadeada
    case ENCADEADA: {
      // Percorre a lista de blocos encadeados a partir do bloco inicial,
      // liberando cada bloco até encontrar o final da cadeia (-1)
      int atual = arquivo->blocoInicial;
      while (atual != -1) {
        int prox = disco[atual].proximo; // Guarda o próximo bloco
        disco[atual].ocupado = 0;
        disco[atual].arquivo = NULL;
        disco[atual].proximo = -1; // Remove o encadeamento
        atual = prox;
      }
      break;
    }

    // Alocação do arquivo de forma indexada
    case INDEXADA: {
      // Percorre a tabela de índices do arquivo e desaloca
      // cada bloco de dados apontado pelo bloco índice
      for (int i = 0; i < arquivo->tamanho; i++) {
        int bloco = arquivo->blocos[i];
        if (bloco != -1) {
          disco[bloco].ocupado = 0;
          disco[bloco].arquivo = NULL;
        }
      }

      // Libera o bloco índice do arquivo
      int blocoIndice = arquivo->blocoInicial;
      disco[blocoIndice].ocupado = 0;
      disco[blocoIndice].arquivo = NULL;
      break;
    }

    default:
      return FALSE;
  }

  // Limpa metadados do arquivo
  arquivo->blocoInicial = -1;
  arquivo->tipo = -1;
  for (int i = 0; i < arquivo->tamanho; i++) {
    arquivo->blocos[i] = -1;
  }

  return TRUE;
}