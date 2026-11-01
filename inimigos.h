#ifndef INIMIGO_H
#define INIMIGO_H
#include<iostream>
#include<vector>
#include<utility>

using namespace std;

class Inimigo{
    protected:
        int vida, dano, recompensa, indicePos = 0;
        int velocidade;
        vector<pair<int, int>> posicao;
    public:
        Inimigo(int v, int d, int r, int vel, vector<pair<int, int>> pos){
            vida = v;
            dano = d; 
            recompensa = r;
            posicao = pos;
            velocidade = vel;
        }
        void mover(){
            if(indicePos < posicao.size()){
                indicePos++;
            }
        }
        
        int getPosicaoX(){
            return posicao[indicePos].first;
        }
        int getPosicaoY(){
            return posicao[indicePos].second;
        }
};

class LeviataDeSilicio : public Inimigo{
    public:
        LeviataDeSilicio(vector<pair<int, int>> pos) : Inimigo(150, 10, 15, 5, pos ){
        }

};

class CuspidorAcido: public Inimigo{
   public:
        CuspidorAcido(vector<pair<int, int>> pos) : Inimigo(100, 7, 10, 7, pos){
        }


};

class ParasitaBiologico: public Inimigo{
    public:
       ParasitaBiologico(vector<pair<int, int>> pos) : Inimigo(70, 5, 5, 10, pos){
        }
};
#endif