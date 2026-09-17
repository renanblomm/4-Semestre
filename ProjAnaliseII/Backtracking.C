#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define N 8

int total_solucoes = 0;

// Exibe o tabuleiro quando as N rainhas forem posicionadas
void mostra_matriz(char tabuleiro[N][N]) {
    total_solucoes++;
    printf("--- Solucao %d ---\n", total_solucoes);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Verifica se a posicao (linha, coluna) esta protegida contra ataques
bool esta_salva(char tabuleiro[N][N], int linha, int coluna) {
    int i, j;

    // 1. Verifica a mesma linha para a esquerda
    for (i = 0; i < coluna; i++) {
        if (tabuleiro[linha][i] == 'Q') {
            return false;
        }
    }

    // 2. Verifica a diagonal superior esquerda
    for (i = linha, j = coluna; i >= 0 && j >= 0; i--, j--) {
        if (tabuleiro[i][j] == 'Q') {
            return false;
        }
    }

    // 3. Verifica a diagonal inferior esquerda
    for (i = linha, j = coluna; i < N && j >= 0; i++, j--) {
        if (tabuleiro[i][j] == 'Q') {
            return false;
        }
    }

    return true;
}

// Algoritmo recursivo com Backtracking para posicionar as rainhas coluna por coluna
void posiciona_rainha(char tabuleiro[N][N], int coluna) {
    // Caso Base: se todas as colunas foram preenchidas com sucesso
    if (coluna == N) {
        mostra_matriz(tabuleiro);
        return;
    }

    // Tenta colocar a rainha em cada linha da coluna atual
    for (int i = 0; i < N; i++) {
        if (esta_salva(tabuleiro, i, coluna)) {
            tabuleiro[i][coluna] = 'Q';              // Escolha

            posiciona_rainha(tabuleiro, coluna + 1); // Passo recursivo

            tabuleiro[i][coluna] = '-';              // Backtracking (desfaz a escolha)
        }
    }
}

int main() {
    char tabuleiro[N][N];

    // Inicializa o tabuleiro com '-'
    memset(tabuleiro, '-', sizeof(tabuleiro));

    // Inicia a busca a partir da coluna 0
    posiciona_rainha(tabuleiro, 0);

    printf("Total de solucoes encontradas: %d\n", total_solucoes);
    return 0;
}