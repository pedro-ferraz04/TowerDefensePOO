#ifndef MAPA_H
#define MAPA_H
#define TAM_M 10
#include <utility>
#include <vector>
#include <iostream>
#include <exception>
#include <string>

using namespace std;

int mapa[TAM_M][TAM_M];

vector<pair<int, int>> trajInimigos = {
    {0, 1}, {1, 1}, {1, 2}, {2, 2}, {3, 2},
    {3, 3}, {3, 4}, {3, 5}, {4, 5}, {5, 5},
    {6, 5}, {6, 4}, {7, 4}, {8, 4}, {8, 5},
    {8, 6}, {8, 7}, {8, 8}, {8, 9}
};

void prepararMapa() {
    for (pair<int, int> aux : trajInimigos) {
        mapa[aux.first][aux.second] = 1;
    }
    mapa[9][9] = 2;
}

bool posicaoValida(int x, int y) {
    if (x < TAM_M && y < TAM_M && x >= 0 && y >= 0) {
        if (mapa[x][y] == 0) {
            return true;
        }
    }
    return false;
}

class ErroCustomizado : public exception {
private:
    string mensagem;
public:
    ErroCustomizado(const std::string& msg) : mensagem(msg) {}
    const char* what() const noexcept override {
        return mensagem.c_str();
    }
};

bool ColocarTorre(int x, int y) {
    if (posicaoValida(x, y)) {
        mapa[x][y] = 3;
        return true;
    }
    throw ErroCustomizado("Posicao Invalida");
}

void imprimirMapa() {
    for (int i = 0; i < TAM_M; i++) {
        for (int j = 0; j < TAM_M; j++) {
            cout << mapa[i][j] << " ";
        }
        cout << endl;
    }
}

#endif