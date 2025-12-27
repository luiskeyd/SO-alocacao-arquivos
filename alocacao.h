/*=============================================================
Arquivo de especificação dos métodos de alocação de memória
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/

#ifndef ALOCACAO_H
#define ALOCACAO_H

int alocacaoContigua(Bloco disco[], Arquivo *arquivo);
int alocacaoEncadeada(Bloco disco[], Arquivo *arquivo);
int alocacaoIndexada(Bloco disco[], Arquivo *arquivo);

#endif