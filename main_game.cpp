#include<iostream>
#include"armas.h"
#include"inimigos.h"
#include"mapa.h"
#include<string>
#include<vector>
#include<utility>


using namespace std;
int main(){
    Inimigo inimigo(150, 10, 15, 5, trajInimigos);
        cout << "(" << inimigo.getPosicaoX() << "," << inimigo.getPosicaoY() << ")" << endl;
        inimigo.mover();
        for(pair<int, int> aux : trajInimigos){
            cout<<"(" << aux.first << "," << aux.second << ")" << endl;
        }
    return 0;
}