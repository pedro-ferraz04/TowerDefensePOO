#ifndef ARMAS_H
#define ARMAS_H

#include <iostream>

using namespace std;

class Armas {
protected:
    int dano, custo, cadencia;
    int alcance, posicaoX, posicaoY;

public:
    Armas(int d, int c, int a, int cad, int x, int y) {
        dano = d;
        custo = c;
        alcance = a;
        posicaoX = x;
        posicaoY = y;
        cadencia = cad;
    }

    bool EstaNoAlcance(int xx, int yy) const {
        if (posicaoX - alcance <= xx && posicaoX + alcance >= xx) {
            if (posicaoY - alcance <= yy && posicaoY + alcance >= yy) {
                return true;
            }
        }
        return false;
    }

    int getPosicaoX() const {
        return posicaoX;
    }
    int getPosicaoY() const {
        return posicaoY;
    }
    int getDano() const {
        return dano;
    }
    int getCusto() const {
        return custo;
    }
    virtual ~Armas() {}
};

class CanhaoDeGauss : public Armas {
public:
    CanhaoDeGauss(int x, int y) : Armas(40, 250, 3, 10, x, y) {
    }
};

class ModuloPEM : public Armas {
public:
    ModuloPEM(int x, int y) : Armas(23, 150, 3, 7, x, y) {
    }
};

class RifleTermico : public Armas {
public:
    RifleTermico(int x, int y) : Armas(10, 70, 2, 30, x, y) {
    }
};

#endif