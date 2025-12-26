#ifndef ARQUIVO_H
#define ARQUIVO_H

#define MAX_ARQUIVOS 20

typedef enum {
  CONTIGUA,
  ENCADEADA,
  INDEXADA
} TipoAlocacao;

typedef struct {
  char nome;
  int tamanho;
  TipoAlocacao tipo;
  int blocoInicial;
  int blocos[MAX_ARQUIVOS];
} Arquivo;

#endif