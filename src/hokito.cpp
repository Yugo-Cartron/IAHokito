#include "hokito.hpp"
#include "case.hpp"

using namespace std;

Hokito::Hokito() {
    int cpt[] = {PIONS_BY_TYPE, PIONS_BY_TYPE, PIONS_BY_TYPE};
    int random = 0;
    for(int i = 0; i<board.size()/2; i++) {
        random = rand() % 3 + 1;
        if ( cpt[random] > 0) { 
            board[i] = Case(Case::BLACK,random);
            cpt[random] --;
        }
    }
    for(int i = board.size()/2; i<board.size(); i++) {
        random = rand() % 3;
        if ( cpt[random] > 0) { 
            board[i] = Case(Case::WHITE,random);
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
    int black_score = calculScore(Case::BLACK);
    int white_score = calculScore(Case::WHITE);
    if(black_score == white_score) 
        return 0;
    if(black_score < white_score) 
        return 1;
    else 
        return -1;
}

vector<int> Hokito::deplacementPossible(const int position, const int valeur, vector<int> deplacement) const {
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

/*

(black) | [white]
- : 1 case
= : 2 cases
≡ : 3 cases
(-,X) : X nombre de pion dans la pile

+-------+-------+-------+-------+-------+-------+
| (≡,1) | (-,1) | (=,1) | (≡,1) | (-,1) | (=,1) |
+-------+-------+-------+-------+-------+-------+
| (=,1) | (-,1) | (≡,1) | (=,1) | (≡,1) | (≡,1) |
+-------+-------+-------+-------+-------+-------+
| (-,1) | (=,1) | (≡,1) | (-,1) | (=,1) | (-,1) |
+-------+-------+-------+-------+-------+-------+
| [=,1] | [=,1] | [≡,1] | [-,1] | [-,1] | [≡,1] |
+-------+-------+-------+-------+-------+-------+
| [-,1] | [-,1] | [=,1] | [≡,1] | [=,1] | [≡,1] |
+-------+-------+-------+-------+-------+-------+
| [=,1] | [≡,1] | [=,1] | [-,1] | [-,1] | [≡,1] |
+-------+-------+-------+-------+-------+-------+

*/

void Hokito::print() const {
    cout << "(black) | [white]" << endl;
    cout << "- : 1 case" << endl;
    cout << "= : 2 cases" << endl;
    cout << "≡ : 3 cases" << endl;
    cout << "(-,X) : X nombre de pions dans la pile" << endl;
    Case c;
    for(int i = 0; i<board.size(); i++) {
        if(i % WIDTH == 0 && i != (board.size() - 1))
            cout << endl << "+-------+-------+-------+-------+-------+-------+" << endl << "|";
        c = board[i];
        if (c.getPile() == 0) 
            cout << "       |";
        else {
            if (c.getCouleur()) { //If c WHITE
                cout << " [";
                if(c.getValeur() == 1) {
                    cout << "-," << c.getPile();
                } else {
                    if(c.getValeur() == 2)
                        cout << "=," << c.getPile();
                    else
                        cout << "≡," << c.getPile();
                }
                cout << "] |";
            } else { //If c BLACK
                cout << " (";
                if(c.getValeur() == 1) {
                    cout << "-," << c.getPile();
                } else {
                    if(c.getValeur() == 2)
                        cout << "=," << c.getPile();
                    else
                        cout << "≡," << c.getPile();
                }
                cout << ") |";
            }
        }
        
    }
    cout << endl << "+-------+-------+-------+-------+-------+-------+" << endl;
}

bool Hokito::is_ended() const {
    for(int i=0; i<board.size(); i++){
        std::vector<int> dep;
        this->deplacementPossible(i, board[i].getValeur(), dep);
        while(dep.size() > 0){
            if(!case_free(dep.at(dep.size()-1))){
                return false;
            }
            dep.pop_back();
        }
    }return true;
}

void Hokito::moves(const int depart, const int arrivee){
    if(tour == 1){
        if(board[depart].getCouleur() != Case::WHITE){
            std::cout << "Ce pion n'est pas à vous" << std::endl;
        }
        std::vector<int> tmp;
        deplacementPossible(depart, board[depart].getValeur(), tmp);
        bool valide =0;
        while(tmp.size() > 0){
            if(tmp.at(tmp.size()-1) == arrivee){
                valide =1;
                break;
            }
            tmp.pop_back();
        }
        if(!valide){
            std::cout << "Vous ne pouvez pas aller là" << std::endl;
        }
        board[arrivee].setPile(board[arrivee].getPile()+1);
        board[arrivee].setCouleur(board[depart].getCouleur());
        board[depart].setPile(0);
        tour = -tour;
    }
    if(tour == -1){
        if(board[depart].getCouleur() != Case::BLACK){
            std::cout << "Ce pion n'est pas à vous" << std::endl;
        }
        std::vector<int> tmp;
        deplacementPossible(depart, board[depart].getValeur(), tmp);
        bool valide =0;
        while(tmp.size() > 0){
            if(tmp.at(tmp.size()-1) == arrivee){
                valide =1;
                break;
            }
            tmp.pop_back();
        }
        if(!valide){
            std::cout << "Vous ne pouvez pas aller là" << std::endl;
        }
        board[arrivee].setPile(board[arrivee].getPile()+1);
        board[arrivee].setCouleur(board[depart].getCouleur());
        board[depart].setPile(0);
        tour = -tour;
    }
}