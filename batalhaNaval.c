#include <stdio.h>
#include <stdbool.h>

// Constantes do programa
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define NUM_NAVIOS 4
#define AGUA 0
#define NAVIO 3

// Enumeração para direções dos navios
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,    // Diagonal para baixo-direita (i, i)
    DIAGONAL_SECUNDARIA    // Diagonal para baixo-esquerda (i, 9-i)
} DirecaoNavio;

// Estrutura para representar um navio
typedef struct {
    int linhaInicial;
    int colunaInicial;
    DirecaoNavio direcao;
    bool posicionado;
} Navio;

// Função para inicializar o tabuleiro com água
void inicializarTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para verificar se uma posição é válida no tabuleiro
bool posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO_TABULEIRO && 
            coluna >= 0 && coluna < TAMANHO_TABULEIRO);
}

// Função para verificar se é possível posicionar um navio
bool podePosicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                         int linhaInicial, int colunaInicial, 
                         DirecaoNavio direcao) {
    
    // Verificar se todas as posições do navio estão dentro do tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;
        
        // Calcular posição baseada na direção
        switch (direcao) {
            case HORIZONTAL:
                coluna += i; // Movimento horizontal para direita
                break;
            case VERTICAL:
                linha += i;  // Movimento vertical para baixo
                break;
            case DIAGONAL_PRINCIPAL:
                linha += i;  // Movimento diagonal para baixo-direita
                coluna += i;
                break;
            case DIAGONAL_SECUNDARIA:
                linha += i;  // Movimento diagonal para baixo-esquerda
                coluna -= i;
                break;
        }
        
        // Verificar se a posição está dentro dos limites
        if (!posicaoValida(linha, coluna)) {
            return false;
        }
        
        // Verificar se não há sobreposição com outro navio
        if (tabuleiro[linha][coluna] != AGUA) {
            return false;
        }
    }
    
    return true;
}

// Função para posicionar um navio no tabuleiro
bool posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], 
                     int linhaInicial, int colunaInicial, 
                     DirecaoNavio direcao) {
    
    // Primeiro verificar se é possível posicionar
    if (!podePosicionarNavio(tabuleiro, linhaInicial, colunaInicial, direcao)) {
        return false;
    }
    
    // Posicionar o navio no tabuleiro
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;
        
        // Calcular posição baseada na direção
        switch (direcao) {
            case HORIZONTAL:
                coluna += i;
                break;
            case VERTICAL:
                linha += i;
                break;
            case DIAGONAL_PRINCIPAL:
                linha += i;
                coluna += i;
                break;
            case DIAGONAL_SECUNDARIA:
                linha += i;
                coluna -= i;
                break;
        }
        
        tabuleiro[linha][coluna] = NAVIO;
    }
    
    return true;
}

// Função para obter o nome da direção como string
const char* obterNomeDirecao(DirecaoNavio direcao) {
    switch (direcao) {
        case HORIZONTAL: return "HORIZONTAL";
        case VERTICAL: return "VERTICAL";
        case DIAGONAL_PRINCIPAL: return "DIAGONAL PRINCIPAL";
        case DIAGONAL_SECUNDARIA: return "DIAGONAL SECUNDÁRIA";
        default: return "DESCONHECIDA";
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL - TABULEIRO COMPLETO ===\n\n");
    
    // Imprimir números das colunas
    printf("    ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    // Imprimir linha separadora
    printf("    ");
    for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
        printf("---");
    }
    printf("\n");
    
    // Imprimir tabuleiro com números das linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%2d |", i); // Número da linha
        
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf(" %d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
    
    printf("\nLegenda: 0 = Água, 3 = Navio\n");
}

// Função para inicializar os navios com configurações pré-definidas
void inicializarNavios(Navio navios[NUM_NAVIOS]) {
    // Navio 1: Horizontal
    navios[0].linhaInicial = 2;
    navios[0].colunaInicial = 3;
    navios[0].direcao = HORIZONTAL;
    navios[0].posicionado = false;
    
    // Navio 2: Vertical
    navios[1].linhaInicial = 5;
    navios[1].colunaInicial = 7;
    navios[1].direcao = VERTICAL;
    navios[1].posicionado = false;
    
    // Navio 3: Diagonal Principal (baixo-direita)
    navios[2].linhaInicial = 1;
    navios[2].colunaInicial = 1;
    navios[2].direcao = DIAGONAL_PRINCIPAL;
    navios[2].posicionado = false;
    
    // Navio 4: Diagonal Secundária (baixo-esquerda)
    navios[3].linhaInicial = 2;
    navios[3].colunaInicial = 8;
    navios[3].direcao = DIAGONAL_SECUNDARIA;
    navios[3].posicionado = false;
}

int main() {
    // Declaração do tabuleiro
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Array de navios
    Navio navios[NUM_NAVIOS];
    
    printf("=== BATALHA NAVAL - NIVEL AVENTUREIRO ===\n");
    printf("Posicionando 4 navios no tabuleiro (2 retos + 2 diagonais)...\n");
    
    // Inicializar o tabuleiro com água
    inicializarTabuleiro(tabuleiro);
    
    // Inicializar os navios com configurações pré-definidas
    inicializarNavios(navios);
    
    // Posicionar todos os navios
    int naviosPosicionados = 0;
    
    for (int i = 0; i < NUM_NAVIOS; i++) {
        printf("\nTentando posicionar navio %d...\n", i + 1);
        printf("Coordenadas: (%d, %d)\n", navios[i].linhaInicial, navios[i].colunaInicial);
        printf("Direção: %s\n", obterNomeDirecao(navios[i].direcao));
        
        if (posicionarNavio(tabuleiro, 
                           navios[i].linhaInicial, 
                           navios[i].colunaInicial, 
                           navios[i].direcao)) {
            printf("✅ Navio %d posicionado com sucesso!\n", i + 1);
            navios[i].posicionado = true;
            naviosPosicionados++;
        } else {
            printf("❌ ERRO: Não foi possível posicionar o navio %d!\n", i + 1);
            printf("   Verifique se as coordenadas são válidas e não há sobreposição.\n");
        }
    }
    
    // Exibir resumo do posicionamento
    printf("\n=== RESUMO DO POSICIONAMENTO ===\n");
    printf("Navios posicionados com sucesso: %d de %d\n", naviosPosicionados, NUM_NAVIOS);
    
    if (naviosPosicionados == NUM_NAVIOS) {
        printf("🎉 Todos os navios foram posicionados com sucesso!\n");
    } else {
        printf("⚠️  Alguns navios não puderam ser posicionados.\n");
    }
    
    // Exibir o tabuleiro final
    exibirTabuleiro(tabuleiro);
    
    // Exibir detalhes dos navios posicionados
    printf("\n=== DETALHES DOS NAVIOS ===\n");
    for (int i = 0; i < NUM_NAVIOS; i++) {
        printf("Navio %d: ", i + 1);
        if (navios[i].posicionado) {
            printf("✅ Posicionado em (%d, %d) - %s\n", 
                   navios[i].linhaInicial, 
                   navios[i].colunaInicial,
                   obterNomeDirecao(navios[i].direcao));
        } else {
            printf("❌ Não posicionado\n");
        }
    }
    
    printf("\n=== PROGRAMA FINALIZADO ===\n");
    
    return 0;
}