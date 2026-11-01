#ifndef ARMAS_H
#define ARMAS_H

#include<iostream>

using namespace std;

class Armas {
protected:
    int dano, custo, velocidade;
    int alcance, posicaoX, posicaoY;
    public:
        Armas(int d, int c, int a, int x, int y, int vel){
            dano = d;
            custo = c;
            alcance = a;
            posicaoX = x;
            posicaoY = y;
            velocidade = vel;
        }
        int EstaNoAlcance(int xx){
            if(posicaoX - alcance <= xx && xx <= posicaoX){
                return 1;
            }
            return 0;
        }


};

class CanhaoDeGauss : public Armas {
    public:
        //CanhaoDeGauss() : Armas(15, 150, 20, ){
        
    

};

class ModuloPEM : public Armas{

};

class RifleTermico : public Armas{

};

#endif