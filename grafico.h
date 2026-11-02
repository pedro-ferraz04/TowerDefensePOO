#ifndef GRAFICO_H
#define GRAFICO_H

#include "raylib.h"
#include "mapa.h"
#include "armas.h"
#include "inimigos.h"
#include "jogador.h"
#include "rodadas.h"
#include <memory>
#include <vector>
#include <string>

const int TAM_CELULA = 60;
const int LARGURA_PAINEL = 220;
const int LARGURA_TELA = TAM_M * TAM_CELULA + LARGURA_PAINEL;
const int ALTURA_TELA = TAM_M * TAM_CELULA;

enum class Fase { POSICIONAR, COMBATE, DERROTA, VITORIA };

// Convenção: mapa[x][y], x é a linha e y é a coluna.
// Na tela, a coluna vira o eixo horizontal e a linha, o vertical.
inline Vector2 centroCelula(int x, int y) {
    return { y * TAM_CELULA + TAM_CELULA / 2.0f, x * TAM_CELULA + TAM_CELULA / 2.0f };
}

inline void desenharGrade() {
    for (int x = 0; x < TAM_M; x++) {
        for (int y = 0; y < TAM_M; y++) {
            Color cor = LIGHTGRAY;          // 0: vazio
            if (mapa[x][y] == 1) cor = BEIGE;   // caminho dos inimigos
            if (mapa[x][y] == 2) cor = SKYBLUE; // base

            DrawRectangle(y * TAM_CELULA, x * TAM_CELULA, TAM_CELULA, TAM_CELULA, cor);
            DrawRectangleLines(y * TAM_CELULA, x * TAM_CELULA, TAM_CELULA, TAM_CELULA, GRAY);
        }
    }
}

inline Color corDaTorre(int custo) {
    if (custo == 150) return PURPLE;
    if (custo == 250) return GOLD;
    return ORANGE;
}

inline void desenharTorres(const std::vector<std::unique_ptr<Armas>>& armas, bool mostrarAlcance) {
    for (const auto& torre : armas) {
        int x = torre->getPosicaoX();
        int y = torre->getPosicaoY();
        int a = torre->getAlcance();

        if (mostrarAlcance) {
            // EstaNoAlcance usa um quadrado de (2a+1) células centrado na torre
            DrawRectangleLines((y - a) * TAM_CELULA, (x - a) * TAM_CELULA,
                               (2 * a + 1) * TAM_CELULA, (2 * a + 1) * TAM_CELULA,
                               Fade(BLUE, 0.5f));
        }

        Vector2 c = centroCelula(x, y);
        DrawCircleV(c, 20, corDaTorre(torre->getCusto()));
        DrawCircleLinesV(c, 20, BLACK);
    }
}

inline void desenharInimigos(const std::vector<pont>& inimigos, int tick) {
    for (const pont& inim : inimigos) {
        // Ainda não entrou no mapa ou já saiu de cena
        if (inim.tickEntrada > tick) continue;
        if (!inim.ptr->estaVivo() || inim.ptr->chegouAoFim()) continue;

        Vector2 c = centroCelula(inim.ptr->getPosicaoX(), inim.ptr->getPosicaoY());
        DrawCircleV(c, 16, RED);

        // Barra de vida acima do inimigo
        float fracao = (float)inim.ptr->getVida() / inim.ptr->getVidaMax();
        DrawRectangle((int)c.x - 20, (int)c.y - 30, 40, 6, DARKGRAY);
        DrawRectangle((int)c.x - 20, (int)c.y - 30, (int)(40 * fracao), 6, GREEN);
    }
}

inline void desenharPainel(const Jogador& jogador, int rodada, Fase fase,
                           int escolha, const std::string& msg) {
    int x = TAM_M * TAM_CELULA + 10;
    DrawRectangle(TAM_M * TAM_CELULA, 0, LARGURA_PAINEL, ALTURA_TELA, DARKGRAY);

    DrawText(TextFormat("Rodada: %d/7", rodada), x, 20, 24, WHITE);
    DrawText(TextFormat("Vida da base: %d", jogador.getVidaBase()), x, 60, 20, WHITE);
    DrawText(TextFormat("Dinheiro: %d", jogador.getDinheiro()), x, 90, 20, WHITE);

    if (fase == Fase::POSICIONAR) {
        const char* nomes[] = {"", "1 Rifle Termico (70)", "2 Modulo PEM (150)", "3 Canhao Gauss (250)"};
        DrawText("Torre selecionada:", x, 140, 20, WHITE);
        DrawText(nomes[escolha], x, 170, 18, YELLOW);
        DrawText("Clique na grade para", x, 230, 16, LIGHTGRAY);
        DrawText("posicionar a torre.", x, 250, 16, LIGHTGRAY);
        DrawText("ENTER: iniciar rodada", x, 280, 16, LIGHTGRAY);
        DrawText(msg.c_str(), x, 320, 18, GREEN);
    }
    else if (fase == Fase::COMBATE) {
        DrawText("Combate...", x, 140, 22, WHITE);
    }
    else if (fase == Fase::DERROTA) {
        DrawText("DERROTA", x, 140, 30, RED);
    }
    else {
        DrawText("VITORIA", x, 140, 30, GREEN);
    }
}

#endif