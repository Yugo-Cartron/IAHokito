#include "hokito.hpp"

Hokito::Hokito(){
    int cpt[] = {PIONS_BY_TYPE, PIONS_BY_TYPE, PIONS_BY_TYPE};
    int random = 0;
    for(int i = 0; i<board.size(); i++) {
        random = rand() % 3;
        if ( cpt[random] > 0) { 
            board[i] = Case();
            cpt[random] --;
        }
    }
}

int Hokito::calculScore(bool couleur) {

}