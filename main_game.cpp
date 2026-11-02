#include "armas.h"
#include "inimigos.h"
#include "mapa.h"
#include "jogador.h"
#include "rodadas.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <exception>
#include <algorithm>
#include <memory>
#include <limits>

using namespace std;

int main() {
    prepararMapa();

    // Criação dos inimigos

    vector<pont> inimigo;

    // Fase de posicionamento das torres
    int x = 0, y = 0;
    char continuar = 's';
    cout << "posicione a torre:" << endl;
    vector<unique_ptr<Armas>> armas;
    Jogador jogador(100, 100);
    for (int rodadas = 1; rodadas <= 7; rodadas++) {
        inimigo = montarRodada(rodadas);
        continuar = 's';
        cout << "\n=== Rodada " << rodadas << " ===" << endl;
        cout << "Posicione suas torres." << endl;
        cout << "Dinheiro do jogador: " << jogador.getDinheiro() << endl;
        cout << "Escolha um tipo de torre para posicionar: " << endl;
        cout << "1. Rifle Termico (custo: 70)" << endl;
        cout << "2. Modulo PEM (custo: 150)" << endl;
        cout << "3. Canhao de Gauss (custo: 250)" << endl;
        int escolha = 0;
        cin >> escolha;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int custo = 70;
        if (escolha == 2) {
            custo = 150;
        }
        else if (escolha == 3) {
            custo = 250;
        }
        else if (escolha != 1) {
            cout << "Escolha invalida, sera criado um Rifle Termico." << endl;
        }

        while (continuar == 's' || continuar == 'S') {
            cin >> x >> y;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Entrada invalida, digite dois numeros." << endl;
                continue;
            }
            try {
                if (jogador.getDinheiro() < custo) {
                    throw ErroCustomizado("Dinheiro insuficiente para criar torre");
                }
                if (ColocarTorre(x, y)) {
                    if (escolha == 2) {
                        armas.push_back(make_unique<ModuloPEM>(x, y));
                    }
                    else if (escolha == 3) {
                        armas.push_back(make_unique<CanhaoDeGauss>(x, y));
                    }
                    else {
                        armas.push_back(make_unique<RifleTermico>(x, y));
                    }
                    cout << "Criado" << endl;
                    jogador.gastarDinheiro(armas.back()->getCusto());
                }
            }
            catch (const ErroCustomizado& e) {
                cout << e.what() << endl;
            }

            cout << "Posicionar outra torre? (s/n): ";
            cin >> continuar;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N') {
                cout << "Responda s ou n: ";
                cin >> continuar;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }

        // Combate: um tick por volta
        for (int i = 0; i < 40; i++) {

            // Laço de inimigos: cada um age uma vez por tick
            for (pont& inim : inimigo) {

                // Ainda não entrou no mapa
                if (inim.tickEntrada > i) {
                    continue;
                }
                // Já morreu ou já chegou ao fim
                if (!inim.ptr->estaVivo() || inim.ptr->chegouAoFim()) {
                    continue;
                }

                cout << "Inimigo entrada " << inim.tickEntrada
                     << " em: (" << inim.ptr->getPosicaoX() << ", " << inim.ptr->getPosicaoY() << ")"
                     << " vida " << inim.ptr->getVida()
                     << " tick " << i << endl;

                // Guarda o estado antes do ataque, para detectar a morte no tick
                bool estavaVivo = inim.ptr->estaVivo();

                // Dano de cada torre que alcança o inimigo
                for (const unique_ptr<Armas>& torre : armas) {
                    if (inim.ptr->estaVivo() && torre->EstaNoAlcance(inim.ptr->getPosicaoX(), inim.ptr->getPosicaoY())) {
                        inim.ptr->receberDano(torre->getDano());
                    }
                }

                // Morte: recompensa uma única vez
                if (estavaVivo && !inim.ptr->estaVivo()) {
                    cout << "Inimigo morto" << endl;
                    jogador.receberDinheiro(inim.ptr->getRecompensa());
                }

                // Movimento
                inim.ptr->mover();

                // Chegada ao fim: a base recebe o dano uma única vez
                if (inim.ptr->chegouAoFim() && inim.ptr->estaVivo()) {
                    jogador.receberDano(inim.ptr->getDano());
                }
                if (jogador.getVidaBase() <= 0) {
                    cout << "DERROTA" << endl;
                    return 0;
                }
            }

            // Remove inimigos mortos ou que chegaram ao fim
            auto it = remove_if(inimigo.begin(), inimigo.end(), [](const pont& inim) {
                return !inim.ptr->estaVivo() || inim.ptr->chegouAoFim();
            });
            inimigo.erase(it, inimigo.end());
        }
    }

    // Resultado final
    for_each(armas.begin(), armas.end(), [](const unique_ptr<Armas>& torre) {
        cout << "Torre em: (" << torre->getPosicaoX() << ", " << torre->getPosicaoY() << ")" << endl;
    });
    cout << "VITORIA" << endl;
    cout << "Vida da base: " << jogador.getVidaBase() << endl;
    cout << "Dinheiro do jogador: " << jogador.getDinheiro() << endl;

    return 0;
}