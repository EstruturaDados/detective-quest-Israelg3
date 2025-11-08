#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Cria uma nova sala dinamicamente
Sala* criarSala(const char *nome) {
    Sala *nova = (Sala*) malloc(sizeof(Sala));
    strcpy(nova->nome, nome);
    nova->esquerda = NULL;
    nova->direita = NULL;
    return nova;
}

// Exploração interativa da mansão
void explorarSalas(Sala *atual) {
    char escolha;

    while (atual != NULL) {
        printf("\n📍 Você está na sala: %s\n", atual->nome);

        if (atual->esquerda == NULL && atual->direita == NULL) {
            printf("🔍 Fim do caminho! Não há mais saídas.\n");
            break;
        }

        printf("Para onde deseja ir?\n");
        if (atual->esquerda) printf("  [e] Ir para a esquerda (%s)\n", atual->esquerda->nome);
        if (atual->direita)  printf("  [d] Ir para a direita (%s)\n", atual->direita->nome);
        printf("  [s] Sair da exploração\n> ");

        scanf(" %c", &escolha);

        if (escolha == 'e' && atual->esquerda != NULL) {
            atual = atual->esquerda;
        } else if (escolha == 'd' && atual->direita != NULL) {
            atual = atual->direita;
        } else if (escolha == 's') {
            printf("🚪 Você decidiu sair da mansão.\n");
            break;
        } else {
            printf("❌ Opção inválida. Tente novamente.\n");
        }
    }
}

// Libera memória da árvore
void liberarSalas(Sala *raiz) {
    if (raiz == NULL) return;
    liberarSalas(raiz->esquerda);
    liberarSalas(raiz->direita);
    free(raiz);
}

// Monta a árvore binária da mansão
Sala* montarMansao() {
    Sala *hall = criarSala("Hall de Entrada");
    Sala *biblioteca = criarSala("Biblioteca");
    Sala *cozinha = criarSala("Cozinha");
    Sala *escritorio = criarSala("Escritório");
    Sala *jardim = criarSala("Jardim");
    Sala *despensa = criarSala("Despensa");
    Sala *salaJantar = criarSala("Sala de Jantar");

    hall->esquerda = biblioteca;
    hall->direita = cozinha;

    biblioteca->esquerda = escritorio;
    biblioteca->direita = jardim;

    cozinha->esquerda = despensa;
    cozinha->direita = salaJantar;

    return hall;
}

int main() {
    printf("🏰 Bem-vindo ao Detective Quest - Nível Novato!\n");
    printf("Explore a mansão e descubra seus segredos...\n");

    Sala *mansao = montarMansao();
    explorarSalas(mansao);
    liberarSalas(mansao);

    printf("\n🔚 Fim da exploração. Até a próxima investigação!\n");
    return 0;
}
