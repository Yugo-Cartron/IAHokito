#include "hokito.hpp"
#include "case.hpp"

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

std::vector<int> Hokito::deplacementPossible(const int position, const int valeur, std::vector<int> deplacement) const {
    if (board[position].getValeur() == 1){
        //on regarde si les différentes possibilités sont égales à 1 ou -1 quand on les fait modulo la largeur et qu'on les soustraient à la position
        //(on fait +1 à chaque position pour commencer le tableau à 1)
        if (((position-1+1 % WIDTH) - (position+1 % WIDTH)) == -1 || ((position-1+1 % WIDTH) - (position+1 % WIDTH)) == 1) {
            deplacement.push_back(position-1);
        }        
        if (((position+1+1 % WIDTH) - (position+1 % WIDTH)) == -1 || ((position+1+1 % WIDTH) - (position+1 % WIDTH)) == 1) {
            deplacement.push_back(position+1);
        }        
        if (position-WIDTH > 0) {
            deplacement.push_back(position-WIDTH);
        }        
        if (position+WIDTH < WIDTH*HEIGHT) {
            deplacement.push_back(position+WIDTH);
        }
        return deplacement;
    }
    else if (board[position].getValeur() == 2 || board[position].getValeur() == 3){
        if (((position-1+1 % WIDTH) - (position+1 % WIDTH)) == -1 || ((position-1+1 % WIDTH) - (position+1 % WIDTH)) == 1) {
            this->deplacementPossible(position-1, valeur -1, deplacement);
        }
        if (((position+1+1 % WIDTH) - (position+1 % WIDTH)) == -1 || ((position+1+1 % WIDTH) - (position+1 % WIDTH)) == 1) {
            this->deplacementPossible(position+1, valeur -1, deplacement);
        }
        if (position-WIDTH > 0) {
            this->deplacementPossible(position-WIDTH, valeur -1, deplacement);
        }
        if (position+WIDTH < WIDTH*HEIGHT) {
            this->deplacementPossible(position+WIDTH, valeur -1, deplacement);
        }
    }
}