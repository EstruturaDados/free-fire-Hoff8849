#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;


typedef struct No {
    Item dados;
    struct No* proximo;
} No;



Item mochilaVetor[10]; 
int qtdItensVetor = 0;

No* mochilaLista = NULL;

int comparacoesSequencial = 0;
int comparacoesBinaria = 0;

void inserirItemVetor() {
    if (qtdItensVetor >= 10) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    Item novo;
    printf("Nome do item: ");
    scanf("%s", novo.nome);

    printf("Tipo do item: ");
    scanf("%s", novo.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    mochilaVetor[qtdItensVetor] = novo;
    qtdItensVetor++;

    printf("\nItem inserido!\n");
}


void removerItemVetor() {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf("%s", nome);

    for (int i = 0; i < qtdItensVetor; i++) {
        if (strcmp(mochilaVetor[i].nome, nome) == 0) {
            for (int j = i; j < qtdItensVetor - 1; j++)
                mochilaVetor[j] = mochilaMochila[j + 1];

            qtdItensVetor--;
            printf("Item removido!\n");
            return;
        }
    }
    printf("Item não encontrado.\n");
}


void listarVetor() {
    printf("\n--- Itens do Vetor ---\n");
    if (qtdItensVetor == 0) {
        printf("Mochila vazia.\n");
        return;
    }

    for (int i = 0; i < qtdItensVetor; i++) {
        printf("%d. %s | %s | %d\n", i+1,
               mochilaVetor[i].nome,
               mochilaVetor[i].tipo,
               mochilaVetor[i].quantidade);
    }
}


int buscarSequencialVetor(char nome[]) {
    comparacoesSequencial = 0;

    for (int i = 0; i < qtdItensVetor; i++) {
        comparacoesSequencial++;
        if (strcmp(mochilaVetor[i].nome, nome) == 0)
            return i;
    }
    return -1;
}


void ordenarVetor() {
    for (int i = 0; i < qtdItensVetor - 1; i++) {
        int min = i;
        for (int j = i+1; j < qtdItensVetor; j++)
            if (strcmp(mochilaVetor[j].nome, mochilaVetor[min].nome) < 0)
                min = j;

        if (min != i) {
            Item temp = mochilaVetor[i];
            mochilaVetor[i] = mochilaVetor[min];
            mochilaVetor[min] = temp;
        }
    }
    printf("\nVetor ordenado por nome!\n");
}


int buscarBinariaVetor(char nome[]) {
    comparacoesBinaria = 0;

    int ini = 0, fim = qtdItensVetor - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        comparacoesBinaria++;

        int cmp = strcmp(nome, mochilaVetor[meio].nome);

        if (cmp == 0)
            return meio;
        else if (cmp < 0)
            fim = meio - 1;
        else
            ini = meio + 1;
    }
    return -1;
}


void inserirItemLista() {
    No* novo = (No*) malloc(sizeof(No));

    printf("Nome do item: ");
    scanf("%s", novo->dados.nome);

    printf("Tipo do item: ");
    scanf("%s", novo->dados.tipo);

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);

    novo->proximo = mochilaLista;
    mochilaLista = novo;

    printf("\nItem inserido na lista!\n");
}


void removerItemLista() {
    char nome[30];
    printf("\nNome do item a remover: ");
    scanf("%s", nome);

    No* atual = mochilaLista;
    No* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->dados.nome, nome) == 0) {
            if (anterior == NULL)
                mochilaLista = atual->proximo;
            else
                anterior->proximo = atual->proximo;

            free(atual);
            printf("Item removido!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Item não encontrado.\n");
}


void listarLista() {
    printf("\n--- Itens da Lista ---\n");

    No* atual = mochilaLista;
    if (atual == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    while (atual != NULL) {
        printf("%s | %s | %d\n",
               atual->dados.nome,
               atual->dados.tipo,
               atual->dados.quantidade);
        atual = atual->proximo;
    }
}


No* buscarSequencialLista(char nome[]) {
    comparacoesSequencial = 0;

    No* atual = mochilaLista;

    while (atual != NULL) {
        comparacoesSequencial++;

        if (strcmp(atual->dados.nome, nome) == 0)
            return atual;

        atual = atual->proximo;
    }
    return NULL;
}


int main() {
    int opcao, estrutura;
    char nomeBusca[30];

    while (1) {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1 - Usar mochila com Vetor\n");
        printf("2 - Usar mochila com Lista Encadeada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &estrutura);

        if (estrutura == 0) break;

        if (estrutura == 1) {
            while (1) {
                printf("\n=== Mochila (Vetor) ===\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Ordenar itens\n");
                printf("5 - Busca Sequencial\n");
                printf("6 - Busca Binária\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);

                if (opcao == 0) break;

                switch (opcao) {
                    case 1: inserirItemVetor(); break;
                    case 2: removerItemVetor(); break;
                    case 3: listarVetor(); break;
                    case 4: ordenarVetor(); break;
                    case 5:
                        printf("Nome para buscar: ");
                        scanf("%s", nomeBusca);
                        int pos = buscarSequencialVetor(nomeBusca);
                        if (pos >= 0)
                            printf("Encontrado: %s (%d comparações)\n", mochilaVetor[pos].nome, comparacoesSequencial);
                        else
                            printf("Não encontrado (%d comparações)\n", comparacoesSequencial);
                        break;
                    case 6:
                        printf("Nome para buscar: ");
                        scanf("%s", nomeBusca);
                        int pos2 = buscarBinariaVetor(nomeBusca);
                        if (pos2 >= 0)
                            printf("Encontrado: %s (%d comparações)\n", mochilaVetor[pos2].nome, comparacoesBinaria);
                        else
                            printf("Não encontrado (%d comparações)\n", comparacoesBinaria);
                        break;
                }
            }
        }

        if (estrutura == 2) {
            while (1) {
                printf("\n=== Mochila (Lista Encadeada) ===\n");
                printf("1 - Inserir item\n");
                printf("2 - Remover item\n");
                printf("3 - Listar itens\n");
                printf("4 - Buscar item\n");
                printf("0 - Voltar\n");
                printf("Opcao: ");
                scanf("%d", &opcao);

                if (opcao == 0) break;

                switch (opcao) {
                    case 1: inserirItemLista(); break;
                    case 2: removerItemLista(); break;
                    case 3: listarLista(); break;
                    case 4:
                        printf("Nome: ");
                        scanf("%s", nomeBusca);
                        No* achado = buscarSequencialLista(nomeBusca);
                        if (achado)
                            printf("Encontrado: %s (%d comparações)\n", achado->dados.nome, comparacoesSequencial);
                        else
                            printf("Não encontrado (%d comparações)\n", comparacoesSequencial);
                        break;
                }
            }
        }
    }

    printf("\nEncerrando o sistema...\n");
    return 0;
}
