#ifndef JOGADOR_H
#define JOGADOR_H
#include <utility>
#include <vector>
#include <iostream>
#include <exception>
#include <string>

using namespace std;

class Jogador {
protected:
    int vidaBase, dinheiro;

public:
    Jogador(int v, int d) {
        vidaBase = v;
        dinheiro = d;
    }
    int getVidaBase() const {
        return vidaBase;
    }
    int getDinheiro() const {
        return dinheiro;
    }
    void receberDano(int d) {
        vidaBase -= d;
        if (vidaBase < 0) {
            vidaBase = 0;
        }
    }
    void receberDinheiro(int d) {
        dinheiro += d;
    }
    bool estaVivo() const {
        return vidaBase > 0;
    }
    bool gastarDinheiro(int d) {
        if (dinheiro >= d) {
            dinheiro -= d;
            return true;
        }
        return false;
    }
};

#endif