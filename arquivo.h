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
  int blocoInicial; // só pra encadeada 
  int blocos[MAX_ARQUIVOS]; // só pra indexada
} Arquivo;

 extern Arquivo inicializarArquivo(char nome, int tamanho, TipoAlocacao tipo);

#endif