/*=============================================================
Arquivo de especificação da estrutura do arquivo e suas funções
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueias, Glezier Montalvane.
Data: Dezembro de 2025
===============================================================*/

#ifndef ARQUIVO_H
#define ARQUIVO_H

#define MAX_ARQUIVOS 20

typedef enum { // Tipos de alocação
  CONTIGUA,
  ENCADEADA,
  INDEXADA
} TipoAlocacao;

typedef struct {
  char nome;
  int tamanho;
  TipoAlocacao tipo;
  int blocoInicial; // Utilizada somente na encadeada 
  int blocos[MAX_ARQUIVOS]; // Utilizada somente na indexada
} Arquivo;

// Função para inicializar um arquivo
extern Arquivo *inicializarArquivo(char nome, int tamanho, TipoAlocacao tipo);

#endif