#include <time.h>
#include <algorithm>
#include "hokito.hpp"
#include "case.hpp"

using namespace std;

Hokito::Hokito() {
    tour = true;
    int cptBlack[] = {PIONS_BY_TYPE, PIONS_BY_TYPE, PIONS_BY_TYPE};
    int random = 0;
    srand(time(NULL));
    for(int i = 0; i<board.size()/2; i++) {
        random = rand() % 3 + 1;
        if ( cptBlack[random-1] > 0) { 
            board[i] = Case(Case::BLACK,random);
            cptBlack[random-1] --;
        } else 
            i--;
    }
    int cptWhite[] = {PIONS_BY_TYPE, PIONS_BY_TYPE, PIONS_BY_TYPE};
    for(int i = board.size()/2; i<board.size(); i++) {
        random = rand() % 3 + 1;
        if ( cptWhite[random-1] > 0) { 
            board[i] = Case(Case::WHITE,random);
            cptWhite[random-1] --;
        } else 
            i--;
    }
}

int Hokito::calculScore(bool couleur) const {
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
int Hokito::whoWins() const{
    int black_score = calculScore(Case::BLACK);
    cout << "Score <noirs> : " << black_score << endl;
    int white_score = calculScore(Case::WHITE);
    cout << "Score [blancs] : " << white_score << endl;
    if(black_score == white_score) {
        cout << "Egalité !" << endl;
        return 0; 
    } if(black_score < white_score) {
        cout << "Victoire des [blancs] !" << endl; 
        return 1;        
    } else {
        cout << "Victoire des <noirs> !" << endl;
        return -1;        
    }

}

/*void Hokito::deplacementPossible(const int position, const int valeur, vector<int>* deplacement) const {
    if(valeur == 1){
        if( position >= WIDTH ) {
            //cout << position-WIDTH<< " " << endl;
            deplacement->push_back(position-WIDTH);
        }
            
        if (position < HEIGHT*(WIDTH-1)) {
            //cout << position+WIDTH<< " " << endl;
            deplacement->push_back(position+WIDTH);
        }
        if (position % WIDTH != 0) {
            //cout << position-1<< " " << endl;
            deplacement->push_back(position-1);
        }
        if (position % WIDTH != 5){
            //cout << position+1<< " " << endl;
            deplacement->push_back(position+1);
        }
    }
    if(valeur == 2 || valeur == 3) {
        if( position >= WIDTH ) 
            deplacementPossible(position - WIDTH, valeur - 1, deplacement);
        if (position < HEIGHT*(WIDTH-1)) 
            deplacementPossible(position + WIDTH, valeur - 1, deplacement);
        if (position % WIDTH != 0) 
            deplacementPossible(position - 1, valeur - 1, deplacement);
        if (position % WIDTH != 5)
            deplacementPossible(position + 1, valeur - 1, deplacement);
    }
}*/

void Hokito::deplacementPossible(int depart, vector<int>* deplacement) {
    Case tmp = board[depart];
    bool isPile = tmp.isPile();
    board[depart].setPile(0);
    recDeplacement(depart, tmp.getValeur(), isPile, deplacement);
    board[depart] = tmp;
}

void Hokito::recDeplacement(const int position, const int valeur, const bool isPile, vector<int>* deplacement) const {
    //Condition d'arrêt
    if(valeur == 1) {

        //Déplacement vers le haut
        if(position >= WIDTH) {
            int tmp = position;
            bool trouve = false;
            while( (tmp >= WIDTH) && !trouve) {
                tmp -= WIDTH;
                
                //On cherche une case non vide où s'arrêter
                if( !case_free(tmp) ){
                    trouve = true;

                    //On vérifie la compatibilité
                    if(board[tmp].isPile() == isPile) {
                        if(count(deplacement->begin(), deplacement->end(), tmp) == 0)
                            deplacement->push_back(tmp);
                    }                   
                }
            } 
        }

        //Déplacement vers le bas
        if(position < HEIGHT*(WIDTH-1)) {
            int tmp = position;
            bool trouve = false;
            while( (tmp < HEIGHT*(WIDTH-1)) && !trouve) {
                tmp += WIDTH;
                
                //On cherche une case non vide où s'arrêter
                if( !case_free(tmp) ){
                    trouve = true;

                    //On vérifie la compatibilité
                    if(board[tmp].isPile() == isPile) {
                        if(count(deplacement->begin(), deplacement->end(), tmp) == 0)
                            deplacement->push_back(tmp);
                    }                   
                }
            } 
        }

        //Déplacement vers la gauche
        if(position % WIDTH != 0) {
            int tmp = position;
            bool trouve = false;
            while( (tmp % WIDTH != 0) && !trouve) {
                tmp --;
                
                //On cherche une case non vide où s'arrêter
                if( !case_free(tmp) ){
                    trouve = true;

                    //On vérifie la compatibilité
                    if(board[tmp].isPile() == isPile) {
                        if(count(deplacement->begin(), deplacement->end(), tmp) == 0)
                            deplacement->push_back(tmp);
                    }
                }
            } 
        }

        //Déplacement vers la droite
        if(position % WIDTH != 5) {
            int tmp = position;
            bool trouve = false;
            while( (tmp % WIDTH != 5) && !trouve) {
                tmp ++;
                
                //On cherche une case non vide où s'arrêter
                if( !case_free(tmp) ){
                    trouve = true;

                    //On vérifie la compatibilité
                    if(board[tmp].isPile() == isPile) {
                        if(count(deplacement->begin(), deplacement->end(), tmp) == 0)
                            deplacement->push_back(tmp);
                    }
                }
            } 
        }
    }

    //Récursivité
    if( valeur == 2 || valeur == 3) {

        //Déplacement vers le haut
        if(position >= WIDTH) {
            int tmp = position;
            bool trouve = false;
            while( (tmp >= WIDTH) && !trouve) {
                tmp -= WIDTH;
                
                //On cherche une case non vide pour continuer
                if( !case_free(tmp) ){
                    trouve = true;
                    recDeplacement(tmp, valeur - 1, isPile, deplacement);
                }
            } 
        }

        //Déplacement vers le bas
        if(position < HEIGHT*(WIDTH-1)) {
            int tmp = position;
            bool trouve = false;
            while( (tmp < HEIGHT*(WIDTH-1)) && !trouve) {
                tmp += WIDTH;
                
                //On cherche une case non vide pour continuer
                if( !case_free(tmp) ){
                    trouve = true;
                    recDeplacement(tmp, valeur - 1, isPile, deplacement);           
                }
            } 
        }

        //Déplacement vers la gauche
        if(position % WIDTH != 0) {
            int tmp = position;
            bool trouve = false;
            while( (tmp % WIDTH != 0) && !trouve) {
                tmp --;
                
                //On cherche une case non vide pour continuer
                if( !case_free(tmp) ){
                    trouve = true;
                    recDeplacement(tmp, valeur - 1, isPile, deplacement);                  
                }
            } 
        }

        //Déplacement vers la droite
        if(position % WIDTH != 5) {
            int tmp = position;
            bool trouve = false;
            while( (tmp % WIDTH != 5) && !trouve) {
                tmp ++;
                
                //On cherche une case non vide où s'arrêter
                if( !case_free(tmp) ){
                    trouve = true;
                    recDeplacement(tmp, valeur - 1, isPile, deplacement);   
                }
            } 
        }
    }
}

/*
void Hokito::deplacementPossibleReel(const int position, const int valeur, vector<int>* deplacement, bool isPile) const {
    if(valeur == 1){
        if( position >= WIDTH) {
            int where = WIDTH;
            bool ok = true;
            while(case_free(position - where)){
                if (position - where < 0) {
                    ok = false;
                    break;
                }
                where = where + WIDTH;
            
            } if (ok && (board[position-where].isPile() == isPile )) {
                //Pour que le déplacement soit possible il faut que :
                // ok : Vérifie si la case existe et n'est pas vide
                // isPile : vérifie qu'une pile aille sur une pile 
                deplacement->push_back(position-where);
            }
        }
        if (position < HEIGHT*(WIDTH-1)) {
            int where = WIDTH;
            bool ok = true;
            while(case_free(position + where)){
                if (position + where > WIDTH*HEIGHT-1) {
                    ok = false;
                    break;
                }
                where = where + WIDTH;
            } if (ok && (board[position+where].isPile() == isPile ) ){
                deplacement->push_back(position+where);
            }
        }
        if (position % WIDTH != 0) {
            int where = 1;
            bool ok = true;
            while(case_free(position - where)){
                if ((position - where)%6 == 1) {
                    ok = false;
                    break;
                }
                where = where + 1;
            } if (ok && (board[position-where].isPile() == isPile )){
                deplacement->push_back(position-where);
            }
        }
        if (position % WIDTH != 5){
            int where = 1;
            bool ok = true;
            while(case_free(position + where)){
                if ((position + where)%6 == 5) {
                    ok = false;
                    break;
                }
                where = where + 1;
            } if (ok && (board[position+where].isPile() == isPile )){
                deplacement->push_back(position+where);
            }
        }
    }
    if(valeur == 2 || valeur == 3) {
        if( position >= WIDTH){
            int where = WIDTH;
            bool ok = true;
            while(case_free(position - where)){
                if (position - where < 0) {
                    ok = false;
                    break;
                }
                where = where + WIDTH;
            } if (ok){
                deplacementPossibleReel(position - where, valeur - 1, deplacement, isPile);
            }
        }
        if (position < HEIGHT*(WIDTH-1) && !case_free(position)) {
            int where = WIDTH;
            bool ok = true;
            while(case_free(position + where)){
                if (position + where > WIDTH*HEIGHT-1) {
                    ok = false;
                    break;
                }
                where = where + WIDTH;
            } if (ok){
                deplacementPossibleReel(position + where, valeur - 1, deplacement, isPile);
            }
        }
        if (position % WIDTH != 0 && !case_free(position)) {
            int where = 1;
            bool ok = true;
            while(case_free(position - where)){
                if ((position - where)%6 == 0) {
                    ok = false;
                    break;
                }
                where = where + 1;
            } if (ok){
                deplacementPossibleReel(position - where, valeur - 1, deplacement, isPile);
            }
        }
        if (position % WIDTH != 5 && !case_free(position)){
            int where = 1;
            bool ok = true;
            while(case_free(position + where)){
                if ((position - where)%6 == 5) {
                    ok = false;
                    break;
                }
                where = where + 1;
            } if (ok){
                deplacementPossibleReel(position + where, valeur - 1, deplacement, isPile);
            }
        }
    }
} */

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

/* %aybe mettre des <> ou /\ */

void Hokito::print() const {
    /*cout << "<black> | [white]" << endl;
    cout << "- : 1 case" << endl;
    cout << "= : 2 cases" << endl;
    cout << "≡ : 3 cases" << endl;
    cout << "(-,X) : X nombre de pions dans la pile" << endl;*/
    Case c;
    cout << endl << "       0       1       2       3       4       5    " ;
    int line =0;
    for(int i = 0; i<board.size(); i++) {
        if(i % WIDTH == 0 && i != (board.size() - 1)){
            cout << endl << "   +-------+-------+-------+-------+-------+-------+" << endl << line <<"  |";
            line++;
        }
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
                cout << " <";
                if(c.getValeur() == 1) {
                    cout << "-," << c.getPile();
                } else {
                    if(c.getValeur() == 2)
                        cout << "=," << c.getPile();
                    else
                        cout << "≡," << c.getPile();
                }
                cout << "> |";
            }
        }
    }
    cout << endl << "   +-------+-------+-------+-------+-------+-------+" << endl;
}

/**
 * Renvoie true si le joueur n'a plus de déplacement possible
 */
bool Hokito::noMoreMoves(bool couleur) {
    for(int i=0; i<board.size(); i++){
        if(!case_free(i) && board[i].getCouleur() == couleur){   
            vector<int> dep;    
            deplacementPossible(i, &dep);
            if(dep.size() > 0){
                cout << "Il reste des mouvements possibles" << endl;
                return false;
            } 
        }
    }
    cout << "Plus de mouvements possibles" << endl;
    return true;
}

void Hokito::moves(const int depart, const int arrivee){
    board[arrivee].setPile(board[arrivee].getPile()+board[depart].getPile());
    board[arrivee].setCouleur(board[depart].getCouleur());
    board[arrivee].setValeur(board[depart].getValeur());
    board[depart].setPile(0);
    tour = !tour;
}

void Hokito::movesIA(const int coul) {
    int position = rand() % 36;
    vector<int> dep;
    //deplacementPossibleReel(position, board[position].getValeur(), &dep, board[position].isPile());
    if(board[position].getCouleur() == coul){
        deplacementPossible(position, &dep);
    }
    while(case_free(position) || board[position].getCouleur() != coul || dep.size() == 0 ){
        position = rand() % 36;
        deplacementPossible(position, &dep);
    }

    cout << "******** Départ : " << position << endl;
    for (auto arrivee : dep) {
        cout << arrivee << endl;
    }
    
    int arrivee = rand() % dep.size();
    arrivee = dep.at(arrivee);
    cout << "arrivee : " << arrivee << endl;
    moves(position,arrivee);
}

vector<Hokito::Move> Hokito::get_moves(){
    vector<Hokito::Move> res;
    for(int i=0; i<board.size(); i++){
        vector<int> tmp;
        if(board[i].getCouleur() == tour){
            deplacementPossible(i, &tmp);
        }
        for(auto dep : tmp){
            pair<int, int> p = pair<int, int>(i, dep);
            if(count(res.begin(), res.end(), p) == 0)
                res.push_back(p);
        }
    }
    return res;
}

void Hokito::play(int mode) {
    int depart_ligne = 0;
    int depart_colonne = 0;
    int arrivee_ligne = 0;
    int arrivee_colonne = 0;
    int coul = Case::WHITE;
    if (mode == Hokito::PvP) {
        while(!noMoreMoves(coul)) {
            if(tour){
                coul = Case::WHITE;
            }
            else {
                coul = Case::BLACK;
            }
            print();
            cout << "C'est le tour des ";
            if(tour)
                cout << "[blancs]." << endl;
            else {
                cout << "<noirs>." << endl;
            }

            int position, arrivee;

            bool valide = false;
            while(!valide) {
                cout << "Quel pion voulez-vous bouger ?" << endl;
                cout << "Quel colonne ? ";
                cin >> depart_colonne;
                cout << "Quel ligne ? ";
                cin >> depart_ligne;
                position = depart_ligne*WIDTH + depart_colonne;

                //Vérification de la case de départ
                if(board[position].getCouleur() != coul || case_free(position)){
                    if(board[position].getCouleur() != coul) {
                        cout << "Ce pion n'est pas à vous" << endl;
                    } else {
                        cout << "Cette case est vide" << endl;
                    }
                } else {
                    cout << "Où voulez-vous le déplacer ?" << endl;
                    cout << "Quel colonne ? ";
                    cin >> arrivee_colonne;
                    cout << "Quel ligne ? " ;
                    cin >> arrivee_ligne;

                    arrivee = arrivee_ligne*WIDTH + arrivee_colonne;

                    if(case_free(arrivee)){
                        cout << "Vous ne pouvez pas vous arrêter sur une case vide" << endl;
                    } 
                    // else {
                    //     vector<int> tmp;
                    //     //deplacementPossibleReel(position, board[position].getValeur(), &tmp, board[position].isPile());
                    //     deplacementPossible(position, &tmp);
                        
                    //     while(tmp.size() > 0){
                    //         if(tmp.back() == arrivee){
                    //             valide = true;
                    //             break;
                    //         } 
                    //         tmp.pop_back();                            
                    //     }                            
                    // }
                    // if(!valide){
                    //     cout << "Vous ne pouvez pas aller là." << endl;
                    // }

                    vector<int> tmp;
                    deplacementPossible(position, &tmp);
                    if(find(tmp.begin(), tmp.end(), arrivee) == tmp.end()){
                        valide = false;
                        cout << "Vous ne pouvez pas aller là." << endl;
                    } else {
                        valide = true;
                    }
                }
            }
            moves(position, arrivee);
        }
    }
    if (mode == Hokito::PvIA) {
        while(!noMoreMoves(coul)) {
            if(tour){
                coul = Case::WHITE;
            }
            else {
                coul = Case::BLACK;
            }
            print();
            cout << "C'est le tour des ";
            if(tour)
                cout << "[blancs]." << endl;
            else {
                cout << "<noirs>." << endl;
            }
            if(tour){
                int position, arrivee;

                bool valide = false;
                while(!valide) {
                    cout << "Quel pion voulez-vous bouger ?" << endl;
                    cout << "Quel colonne ? ";
                    cin >> depart_colonne;
                    cout << "Quel ligne ? ";
                    cin >> depart_ligne;
                    position = depart_ligne*WIDTH + depart_colonne;

                    //Vérification de la case de départ
                    if(board[position].getCouleur() != coul || case_free(position)){
                        if(board[position].getCouleur() != coul) {
                            cout << "Ce pion n'est pas à vous" << endl;
                        } else {
                            cout << "Ce case est vide" << endl;
                        }
                    } else {
                        cout << "Où voulez-vous le déplacer ?" << endl;
                        cout << "Quel colonne ? ";
                        cin >> arrivee_colonne;
                        cout << "Quel ligne ? " ;
                        cin >> arrivee_ligne;

                        arrivee = arrivee_ligne*WIDTH + arrivee_colonne;

                        if(case_free(arrivee)){
                            cout << "Vous ne pouvez pas vous arrêter sur une case vide" << endl;
                         } 
                        //else {
                        //     vector<int> tmp;
                        //     //deplacementPossibleReel(position, board[position].getValeur(), &tmp, board[position].isPile());
                        //     deplacementPossible(position, &tmp);

                        //     for (auto arrivee : tmp) {
                        //         cout << arrivee << endl;
                        //     }
                            
                        //     while(tmp.size() > 0){
                        //         if(tmp.back() == arrivee){
                        //             valide = true;
                        //             break;
                        //         } 
                        //         tmp.pop_back();                            
                        //     }                            
                        // }

                        // if(!valide){
                        //     cout << "Vous ne pouvez pas aller là." << endl;
                        // }


                        vector<int> tmp;
                        deplacementPossible(position, &tmp);
                        if(find(tmp.begin(), tmp.end(), arrivee) == tmp.end()){
                            valide = false;
                            cout << "Vous ne pouvez pas aller là." << endl;
                        } else{
                            valide = true;
                        }
                    }
                }
                moves(position, arrivee);
            }
            else
                movesIA(Case::BLACK);
        }
    }
    if (mode == Hokito::IAvIA) {
        while(!noMoreMoves(coul)) {
            if(tour){
                coul = Case::WHITE;
            }
            else {
                coul = Case::BLACK;
            }
            print();
            cout << "C'est le tour des ";
            if(tour)
                cout << "[blancs]." << endl;
            else {
                cout << "<noirs>." << endl;
            }
            if(tour){
                movesIA(Case::WHITE);
            }
            else
                movesIA(Case::BLACK);
        }
    }
    print();
    int winner = whoWins();
}