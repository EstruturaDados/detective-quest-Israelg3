#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================
// 🌳 Estrutura da Árvore de Cômodos
// ===========================
typedef struct Sala {
    char nome[50];
    char pista[50];
    struct Sala *esq, *dir;
} Sala;

Sala* criarSala(char *nome, char *pista) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    if (pista != NULL)
        strcpy(nova->pista, pista);
    else
        strcpy(nova->pista, "");
    nova->esq = nova->dir = NULL;
    return nova;
}

// ===========================
// 🔍 Estrutura da Árvore de Pistas (BST)
// ===========================
typedef struct No {
    char pista[50];
    struct No *esq, *dir;
} No;

No* criarNo(char *pista) {
    No *novo = (No*) malloc(sizeof(No));
    strcpy(novo->pista, pista);
    novo->esq = novo->dir = NULL;
    return novo;
}

No* inserirBST(No *raiz, char *pista) {
    if (raiz == NULL)
        return criarNo(pista);
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserirBST(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserirBST(raiz->dir, pista);
    return raiz;
}

void emOrdemBST(No *raiz) {
    if (raiz != NULL) {
        emOrdemBST(raiz->esq);
        printf("🔎 %s\n", raiz->pista);
        emOrdemBST(raiz->dir);
    }
}

// ===========================
// 🧩 Estrutura da Tabela Hash (Pista → Suspeito)
// ===========================
#define TAM 10

typedef struct ItemHash {
    char pista[50];
    char suspeito[50];
    struct ItemHash *prox;
} ItemHash;

ItemHash* tabela[TAM];

// Função de espalhamento simples (soma ASCII dos caracteres)
int hashFunc(char *chave) {
    int soma = 0;
    for (int i = 0; chave[i] != '\0'; i++)
        soma += chave[i];
    return soma % TAM;
}

// Inserção pista → suspeito
void inserirHash(char *pista, char *suspeito) {
    int pos = hashFunc(pista);
    ItemHash *novo = (ItemHash*) malloc(sizeof(ItemHash));
    strcpy(novo->pista, pista);
    strcpy(novo->suspeito, suspeito);
    novo->prox = tabela[pos];
    tabela[pos] = novo;
}

// Exibir todas as associações pista → suspeito
void mostrarHash() {
    printf("\n📂 Relação de Pistas e Suspeitos:\n");
    for (int i = 0; i < TAM; i++) {
        ItemHash *atual = tabela[i];
        while (atual != NULL) {
            printf("🔎 %-25s → 🕵️ %s\n", atual->pista, atual->suspeito);
            atual = atual->prox;
        }
    }
}

// Determinar o suspeito mais citado
void suspeitoMaisCitado() {
    char nomes[50][50];
    int cont[50];
    int total = 0;

    for (int i = 0; i < 50; i++) {
        cont[i] = 0;
        strcpy(nomes[i], "");
    }

    for (int i = 0; i < TAM; i++) {
        ItemHash *atual = tabela[i];
        while (atual != NULL) {
            int encontrado = 0;
            for (int j = 0; j < total; j++) {
                if (strcmp(nomes[j], atual->suspeito) == 0) {
                    cont[j]++;
                    encontrado = 1;
                    break;
                }
            }
            if (!encontrado) {
                strcpy(nomes[total], atual->suspeito);
                cont[total] = 1;
                total++;
            }
            atual = atual->prox;
        }
    }

    int max = 0;
    char suspeitoFinal[50] = "";
    for (int i = 0; i < total; i++) {
        if (cont[i] > max) {
            max = cont[i];
            strcpy(suspeitoFinal, nomes[i]);
        }
    }

    if (max > 0)
        printf("\n⚖️  O suspeito mais citado é: %s (%d pistas)\n", suspeitoFinal, max);
    else
        printf("\nNenhum suspeito foi associado ainda.\n");
}

// ===========================
// ⚙️ Montagem da Mansão
// ===========================
Sala* montarMansao() {
    Sala *hall = criarSala("Hall de Entrada", NULL);
    Sala *biblioteca = criarSala("Biblioteca", "Livro antigo com anotações");
    Sala *salaJantar = criarSala("Sala de Jantar", "Taça quebrada");
    Sala *jardim = criarSala("Jardim", "Pegadas na terra molhada");
    Sala *porao = criarSala("Porão", "Chave enferrujada");
    Sala *escritorio = criarSala("Escritório", "Bilhete rasgado");

    hall->esq = biblioteca;
    hall->dir = salaJantar;
    biblioteca->esq = jardim;
    biblioteca->dir = porao;
    salaJantar->dir = escritorio;

    return hall;
}

// ===========================
// 🎮 Exploração
// ===========================
void explorarSalas(Sala *atual, No **pistas) {
    char opcao;
    while (atual != NULL) {
        printf("\n🏠 Você está em: %s\n", atual->nome);

        if (strlen(atual->pista) > 0) {
            printf("💡 Você encontrou uma pista: %s!\n", atual->pista);
            *pistas = inserirBST(*pistas, atual->pista);
        }

        printf("\nEscolha seu caminho:\n");
        printf("[e] Esquerda\n");
        printf("[d] Direita\n");
        printf("[s] Sair\n");
        printf("👉 ");
        scanf(" %c", &opcao);

        if (opcao == 's') break;
        else if (opcao == 'e') {
            if (atual->esq != NULL) atual = atual->esq;
            else printf("🚪 Caminho à esquerda não existe.\n");
        } else if (opcao == 'd') {
            if (atual->dir != NULL) atual = atual->dir;
            else printf("🚪 Caminho à direita não existe.\n");
        } else {
            printf("❌ Opção inválida!\n");
        }
    }
}

// ===========================
// 🧠 Função Principal
// ===========================
int main() {
    for (int i = 0; i < TAM; i++) tabela[i] = NULL;

    Sala *mansao = montarMansao();
    No *pistas = NULL;

    printf("🏰 Bem-vindo ao Detective Quest - Nível Mestre!\n");
    printf("Explore a mansão, colete pistas e descubra o culpado!\n");

    explorarSalas(mansao, &pistas);

    if (pistas == NULL) {
        printf("\nNenhuma pista foi encontrada.\n");
        return 0;
    }

    // Inserindo manualmente as associações pista → suspeito
    inserirHash("Livro antigo com anotações", "Sr. Black");
    inserirHash("Taça quebrada", "Sra. White");
    inserirHash("Pegadas na terra molhada", "Jardineiro");
    inserirHash("Chave enferrujada", "Sr. Black");
    inserirHash("Bilhete rasgado", "Sra. White");

    printf("\n📜 Pistas coletadas (em ordem alfabética):\n");
    emOrdemBST(pistas);

    mostrarHash();
    suspeitoMaisCitado();

    printf("\n🕵️‍♂️ Mistério encerrado. Parabéns, detetive!\n");
    return 0;
}
