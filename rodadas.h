#ifndef RODADAS_H
#define RODADAS_H

#include "mapa.h"
#include "inimigos.h"
#include <memory>
#include <utility>
#include <vector>

using namespace std;

struct pont {
    unique_ptr<Inimigo> ptr;
    int tickEntrada;
};

vector<pont> montarRodada(int numero) {
    vector<pont> lista;

    if (numero == 1) {
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 0});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 3});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 6});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 8});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 10});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 15});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 16});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 17});
    }
    if (numero == 2) {
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 0});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 3});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 6});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 8});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 10});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 15});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 16});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 17});
    }
    if (numero == 3) {
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 0});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 3});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 6});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 8});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 10});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 15});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 16});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 17});
    }
    if (numero == 4) {
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 0});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 2});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 5});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 7});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 10});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 12});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 15});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 18});
    }
    if (numero == 5) {
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 0});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 1});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 2});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 5});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 7});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 10});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 13});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 16});
    }
    if (numero == 6) {
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 0});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 3});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 6});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 9});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 12});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 13});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 14});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 18});
    }
    if (numero == 7) {
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 0});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 2});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 4});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 6});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 8});
        lista.push_back({move(make_unique<ParasitaBiologico>(trajInimigos)), 10});
        lista.push_back({move(make_unique<CuspidorAcido>(trajInimigos)), 14});
        lista.push_back({move(make_unique<LeviataDeSilicio>(trajInimigos)), 16});
    }

    return lista;
}

#endif