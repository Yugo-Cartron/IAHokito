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