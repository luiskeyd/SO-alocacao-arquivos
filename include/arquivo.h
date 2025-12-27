/*=============================================================
Arquivo de especificação da estrutura do arquivo e suas funções
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#ifndef ARQUIVO_H
#define ARQUIVO_H

#define MAX_ARQUIVOS 20

typedef enum { // tipos de alocação
  CONTIGUA,
  ENCADEADA,
  INDEXADA
} TipoAlocacao;

typedef struct {
  char nome;
  int tamanho;
  TipoAlocacao tipo;
  int blocoInicial; // só pra encadeada 
  int blocos[MAX_ARQUIVOS]; // só pra indexada
} Arquivo;

// Função para inicializar um arquivo
 extern Arquivo inicializarArquivo(char nome, int tamanho, TipoAlocacao tipo);

#endif