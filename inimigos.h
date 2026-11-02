#ifndef INIMIGO_H
#define INIMIGO_H
#include <iostream>
#include <vector>
#include <utility>

using namespace std;

class Inimigo {
protected:
    size_t indicePos = 0;
    int vida, vidaMax, dano, recompensa;
    vector<pair<int, int>> posicao;

public:
    Inimigo(int v, int d, int r, vector<pair<int, int>> pos) {
        vida = v;
        vidaMax = v;
        dano = d;
        recompensa = r;
        posicao = pos;
    }

    void mover() {
        if (indicePos < posicao.size() - 1) {
            indicePos++;
        }
    }

    int getPosicaoX() const {
        return posicao[indicePos].first;
    }
    int getPosicaoY() const {
        return posicao[indicePos].second;
    }
    int getVidaMax() const {
        return vidaMax;
    }
    int getVida() const {
        return vida;
    }
    int getDano() const {
        return dano;
    }
    int getRecompensa() const {
        return recompensa;
    }
    bool chegouAoFim() const {
        return indicePos == posicao.size() - 1;
    }
    void receberDano(int d) {
        vida -= d;
        if (vida < 0) {
            vida = 0;
        }
    }
    bool estaVivo() const {
        return vida > 0;
    }
    virtual ~Inimigo() {}
};

class LeviataDeSilicio : public Inimigo {
public:
    LeviataDeSilicio(vector<pair<int, int>> pos) : Inimigo(150, 15, 35, pos) {
    }
};

class CuspidorAcido : public Inimigo {
public:
    CuspidorAcido(vector<pair<int, int>> pos) : Inimigo(80, 7, 25, pos) {
    }
};

class ParasitaBiologico : public Inimigo {
public:
    ParasitaBiologico(vector<pair<int, int>> pos) : Inimigo(40, 5, 20, pos) {
    }
};

#endif