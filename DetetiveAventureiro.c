#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===========================
// Estrutura da Árvore de Cômodos
// ===========================
typedef struct Sala {
    char nome[50];
    char pista[50]; // Pode conter uma pista (ou vazio)
    struct Sala *esq, *dir;
} Sala;

// Cria uma nova sala com nome e opcionalmente uma pista
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
// Estrutura da Árvore de Pistas (BST)
// ===========================
typedef struct No {
    char pista[50];
    struct No *esq, *dir;
} No;

// Cria um novo nó de pista
No* criarNo(char *pista) {
    No *novo = (No*) malloc(sizeof(No));
    strcpy(novo->pista, pista);
    novo->esq = novo->dir = NULL;
    return novo;
}

// Insere pista na BST
No* inserir(No *raiz, char *pista) {
    if (raiz == NULL)
        return criarNo(pista);
    if (strcmp(pista, raiz->pista) < 0)
        raiz->esq = inserir(raiz->esq, pista);
    else if (strcmp(pista, raiz->pista) > 0)
        raiz->dir = inserir(raiz->dir, pista);
    return raiz;
}

// Exibe pistas em ordem alfabética
void emOrdem(No *raiz) {
    if (raiz != NULL) {
        emOrdem(raiz->esq);
        printf("🔎 %s\n", raiz->pista);
        emOrdem(raiz->dir);
    }
}

// ===========================
// Funções do jogo
// ===========================

// Monta a árvore de cômodos da mansão
Sala* montarMansao() {
    Sala *hall = criarSala("Hall de Entrada", NULL);
    Sala *biblioteca = criarSala("Biblioteca", "Livro antigo com anotações");
    Sala *salaJantar = criarSala("Sala de Jantar", "Taça quebrada");
    Sala *jardim = criarSala("Jardim", "Pegadas na terra molhada");
    Sala *porao = criarSala("Porão", "Chave enferrujada");
    Sala *escritorio = criarSala("Escritório", NULL);

    // Estrutura da árvore de cômodos
    hall->esq = biblioteca;
    hall->dir = salaJantar;
    biblioteca->esq = jardim;
    biblioteca->dir = porao;
    salaJantar->dir = escritorio;

    return hall;
}

// Exploração da mansão
void explorarSalas(Sala *atual, No **raizPistas) {
    char opcao;
    while (atual != NULL) {
        printf("\n🏠 Você está em: %s\n", atual->nome);

        // Se houver pista, adiciona à árvore de pistas
        if (strlen(atual->pista) > 0) {
            printf("💡 Você encontrou uma pista: %s!\n", atual->pista);
            *raizPistas = inserir(*raizPistas, atual->pista);
        }

        printf("\nEscolha seu caminho:\n");
        printf("[e] Ir para a esquerda\n");
        printf("[d] Ir para a direita\n");
        printf("[s] Sair da exploração\n");
        printf("👉 ");
        scanf(" %c", &opcao);

        if (opcao == 's') {
            printf("\nVocê decidiu encerrar a exploração.\n");
            break;
        } else if (opcao == 'e') {
            if (atual->esq != NULL)
                atual = atual->esq;
            else {
                printf("🚪 Caminho à esquerda não existe.\n");
            }
        } else if (opcao == 'd') {
            if (atual->dir != NULL)
                atual = atual->dir;
            else {
                printf("🚪 Caminho à direita não existe.\n");
            }
        } else {
            printf("❌ Opção inválida!\n");
        }
    }
}

// ===========================
// Função principal
// ===========================
int main() {
    Sala *mansao = montarMansao();
    No *pistas = NULL;

    printf("🔍 Bem-vindo ao Detective Quest - Nível Aventureiro!\n");
    printf("Explore a mansão e encontre pistas para resolver o mistério...\n");

    explorarSalas(mansao, &pistas);

    printf("\n📜 Pistas encontradas (em ordem alfabética):\n");
    if (pistas == NULL)
        printf("Nenhuma pista foi encontrada.\n");
    else
        emOrdem(pistas);

    printf("\n🕵️‍♂️ Fim da exploração. Até a próxima investigação!\n");
    return 0;
}
