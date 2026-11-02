#include "grafico.h"
#include <algorithm>
#include <memory>
#include <vector>
#include <string>

using namespace std;

const float INTERVALO_TICK = 0.1f;  // 100 ms por tick
const int TICKS_POR_RODADA = 40;
const int TOTAL_RODADAS = 7;

unique_ptr<Armas> criarTorre(int tipo, int x, int y) {
    if (tipo == 2) return make_unique<ModuloPEM>(x, y);
    if (tipo == 3) return make_unique<CanhaoDeGauss>(x, y);
    return make_unique<RifleTermico>(x, y);
}

int custoDaTorre(int tipo) {
    if (tipo == 2) return 150;
    if (tipo == 3) return 250;
    return 70;
}

// Mesma lógica do laço de combate do main_game.cpp, sem prints.
// Retorna false se a base foi destruída.
bool executarTick(vector<pont>& inimigos, const vector<unique_ptr<Armas>>& armas,
                  Jogador& jogador, int tick) {
    for (pont& inim : inimigos) {
        if (inim.tickEntrada > tick) continue;
        if (!inim.ptr->estaVivo() || inim.ptr->chegouAoFim()) continue;

        bool estavaVivo = inim.ptr->estaVivo();

        for (const unique_ptr<Armas>& torre : armas) {
            if (inim.ptr->estaVivo() &&
                torre->EstaNoAlcance(inim.ptr->getPosicaoX(), inim.ptr->getPosicaoY())) {
                inim.ptr->receberDano(torre->getDano());
            }
        }

        if (estavaVivo && !inim.ptr->estaVivo()) {
            jogador.receberDinheiro(inim.ptr->getRecompensa());
        }

        inim.ptr->mover();

        if (inim.ptr->chegouAoFim() && inim.ptr->estaVivo()) {
            jogador.receberDano(inim.ptr->getDano());
        }
        if (jogador.getVidaBase() <= 0) {
            return false;
        }
    }

    inimigos.erase(remove_if(inimigos.begin(), inimigos.end(),
        [](const pont& inim) {
            return !inim.ptr->estaVivo() || inim.ptr->chegouAoFim();
        }), inimigos.end());
    return true;
}

int main() {
    prepararMapa();

    InitWindow(LARGURA_TELA, ALTURA_TELA, "Tower defense - C++ + raylib");
    SetTargetFPS(60);

    Jogador jogador(100, 100);
    vector<unique_ptr<Armas>> armas;
    vector<pont> inimigos = montarRodada(1);

    Fase fase = Fase::POSICIONAR;
    int rodada = 1;
    int tick = 0;
    int escolha = 1;
    float acumulador = 0.0f;
    string msg;

    while (!WindowShouldClose()) {
        if (fase == Fase::POSICIONAR) {
            if (IsKeyPressed(KEY_ONE))   escolha = 1;
            if (IsKeyPressed(KEY_TWO))   escolha = 2;
            if (IsKeyPressed(KEY_THREE)) escolha = 3;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                int mx = GetMouseX();
                int my = GetMouseY();
                if (mx < TAM_M * TAM_CELULA && my < ALTURA_TELA) {
                    int x = my / TAM_CELULA;   // linha
                    int y = mx / TAM_CELULA;   // coluna
                    int custo = custoDaTorre(escolha);

                    if (jogador.getDinheiro() < custo) {
                        msg = "Dinheiro insuficiente";
                    }
                    else if (!posicaoValida(x, y)) {
                        msg = "Posicao invalida";
                    }
                    else {
                        ColocarTorre(x, y);
                        armas.push_back(criarTorre(escolha, x, y));
                        jogador.gastarDinheiro(custo);
                        msg = "Torre criada";
                    }
                }
            }

            if (IsKeyPressed(KEY_ENTER)) {
                fase = Fase::COMBATE;
                tick = 0;
                acumulador = 0.0f;
                msg.clear();
            }
        }
        else if (fase == Fase::COMBATE) {
            // Tempo real acumulado: um tick a cada 100 ms
            acumulador += GetFrameTime();
            while (acumulador >= INTERVALO_TICK && fase == Fase::COMBATE) {
                acumulador -= INTERVALO_TICK;

                if (!executarTick(inimigos, armas, jogador, tick)) {
                    fase = Fase::DERROTA;
                    break;
                }

                tick++;
                if (tick >= TICKS_POR_RODADA) {
                    rodada++;
                    if (rodada > TOTAL_RODADAS) {
                        fase = Fase::VITORIA;
                    }
                    else {
                        inimigos = montarRodada(rodada);
                        fase = Fase::POSICIONAR;
                        msg.clear();
                    }
                    break;
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenharGrade();
        desenharTorres(armas, fase == Fase::POSICIONAR);
        desenharInimigos(inimigos, tick);
        desenharPainel(jogador, rodada, fase, escolha, msg);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}