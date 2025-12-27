/*=============================================================
Arquivo cntendo a função principal interativa do sistema de
alocação de arquivos
Autores: Willy Kauã, Luis Eduardo, Edmar Miqueiras, Glezier.
Data: Dezembro de 2025
===============================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../include/disco.h"
#include "../include/arquivo.h"
#include "../include/alocacao.h"

void load(){
    for(int i = 1; i<=3; i++){
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    system("clear");
}

int main() {
    printf("=============================================\n");
    printf("Bem-vindo ao sistema de alocação de arquivos!\n");
    printf("=============================================\n");
    printf("Deseja iniciar o sistema? (1 - Sim, 0 - Não): ");
    int iniciar;
    scanf("%d", &iniciar);
    getchar(); 
    system("clear");
    if (!iniciar) {
        printf("Encerrando o sistema. Até mais!\n");
        return 0;
    }

    inicializarDisco();
    printf("Iniciando o sistema\n");
    load();
    printf("Sistema iniciado com sucesso! Pressione qualquer tecla para continuar\n");
    getchar();
    system("clear");


    int flag = 1;
    while (flag) {
        system("clear");
        printf("==============================================\n");
        printf("Seleciona uma opção no menu.\n");
        printf("==============================================\n");
        printf("1. Mostrar estado do disco\n");
        printf("2. Inserir arquivo no disco\n");
        printf("3. Remover arquivo do disco\n");
        printf("4. Limpar disco\n");
        printf("5. Sair do sistema\n");
        printf("==============================================\n");
        printf("\n-> ");
        int opcao;
        scanf("%d", &opcao);
        getchar();
        system("clear");
        switch (opcao) {
            case 1:
                mostrarDisco();
                getchar();
                break;
            case 2:
                printf("Digite o nome do arquivo:(uma letra)");
                char nome;
                scanf("%c", &nome);
                getchar();
                printf("Digite o tamanho do arquivo (em blocos): ");
                int tamanho;
                scanf("%d", &tamanho);
                getchar();
                printf("Escolha o tipo de alocação:\n");
                printf("1. Contígua\n");
                printf("2. Encadeada\n");
                printf("3. Indexada\n");
                printf("-> ");
                int tipoAlocacao;
                scanf("%d", &tipoAlocacao);
                if(tipoAlocacao < 1 || tipoAlocacao > 3) {
                    printf("Tipo de alocação inválido! Operação cancelada.\n");
                    getchar();
                    system("clear");
                    break;
                }
                TipoAlocacao tipo = (TipoAlocacao)(tipoAlocacao - 1);
                Arquivo *arquivo = inicializarArquivo(nome, tamanho, tipo);
                int sucesso = 0;
                switch (tipo) {
                    case CONTIGUA:
                        sucesso = alocacaoContigua(disco, arquivo);
                        break;
                    case ENCADEADA:
                        sucesso = alocacaoEncadeada(disco, arquivo);
                        break;
                    case INDEXADA:
                        sucesso = alocacaoIndexada(disco, arquivo);
                        break;          
                }
                if (sucesso) {
                    printf("Arquivo '%c' alocado com sucesso!\n", nome);
                    getchar();

                } else {
                    printf("Falha ao alocar o arquivo '%c'. Espaço insuficiente no disco.\n", nome);
                    getchar();
                    free(arquivo); // libera memória se falhar
                }
                getchar();
                break;
            case 3:
                printf("Digite o nome do arquivo a ser removido: ");
                char nomeRemover;
                scanf("%c", &nomeRemover);
                getchar();
                Arquivo *arquivoRemover = buscarArquivo(disco, nomeRemover);
                if (arquivoRemover == NULL) {
                    printf("Arquivo '%c' não encontrado no disco.\n", nomeRemover);
                    getchar();
                }
                else {
                    int removido = removerArquivo(disco, arquivoRemover);
                    if (removido) {
                        printf("Arquivo '%c' removido com sucesso!\n", nomeRemover);
                        free(arquivoRemover); // libera memória do arquivo removido
                    } else {
                        printf("Falha ao remover o arquivo '%c'.\n", nomeRemover);
                    }
                    getchar();
                }
                break;
            case 4:
                inicializarDisco();
                load();
                printf("Disco limpo com sucesso!\n");
                getchar();
                break;
            case 5:
                flag = 0;
                printf("Encerrando o sistema. Até mais!\n");
                getchar();
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                getchar();
        }
    }
    return 0;
}