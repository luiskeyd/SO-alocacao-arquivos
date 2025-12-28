/*=============================================================
Arquivo de especificação dos métodos de alocação de memória
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueias, Glezier Montalvane.
Data: Dezembro de 2025
===============================================================*/

#ifndef ALOCACAO_H
#define ALOCACAO_H
#include "disco.h"
#include "arquivo.h"

//Funções para cada tipo de alocação e também remoção de arquivos
int alocacaoContigua(Bloco disco[], Arquivo *arquivo);
int alocacaoEncadeada(Bloco disco[], Arquivo *arquivo);
int alocacaoIndexada(Bloco disco[], Arquivo *arquivo);
int removerArquivo(Bloco disco[], Arquivo *arquivo);

#endif