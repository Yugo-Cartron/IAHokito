#include "hokito.hpp"
#include "case.hpp"

Hokito::Hokito() {
    int cpt[] = {PIONS_BY_TYPE, PIONS_BY_TYPE, PIONS_BY_TYPE};
    int random = 0;
    for(int i = 0; i<board.size()/2; i++) {
        random = rand() % 3;
        if ( cpt[random] > 0) { 
            board[i] = Case(BLACK,random);
            cpt[random] --;
        }
    }
    for(int i = board.size()/2; i<board.size(); i++) {
        random = rand() % 3;
        if ( cpt[random] > 0) { 
            board[i] = Case(WHITE,random);
            cpt[random] --;
        }
    }
}

int Hokito::calculScore(bool couleur) {
    int score = 0;
    for (int i = 0; i<board.size(); i++) {
        Case c = board[i];
        if( c.getPile() > 0) {
            if (couleur == c.getCouleur()) {
                score += (c.getPile() * c.getValeur());
            }
        }
    }
    return score;
}

/* Return 1 if WHITE wins
*  0 if equality
*  -1 if BLACK wins */
int Hokito::whoWins() {
    int black_score = calculScore(BLACK);
    int white_score = calculScore(WHITE);
    if(black_score == white_score) 
        return 0;
    if(black_score < white_score) 
        return 1;
    else 
        return -1;
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