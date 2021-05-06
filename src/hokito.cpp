#include <time.h>
#include <algorithm>
#include "mcts.hpp"
#include "hokito.hpp"
#include "case.hpp"

using namespace std;

Hokito::Hokito() {
    tour = true;
    int cptBlack[] = {PIONS_BY_TYPE, PIONS_BY_TYPE, PIONS_BY_TYPE};
    int random = 0;
    srand(time(NULL));
    for(int i = 0; i<(int) board.size()/2; i++) {
        random = rand() % 3 + 1;
        if ( cptBlack[random-1] > 0) { 
            board[i] = Case(Case::BLACK,random);
            cptBlack[random-1] --;
        } else 
            i--;
    }
    int cptWhite[] = {PIONS_BY_TYPE, PIONS_BY_TYPE, PIONS_BY_TYPE};
    for(int i = (int) board.size()/2; i<(int) board.size(); i++) {
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
    for (int i = 0; i<(int) board.size(); i++) {
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
    // cout << "Score <noirs> : " << black_score << endl;
    int white_score = calculScore(Case::WHITE);
    // cout << "Score [blancs] : " << white_score << endl;
    if(black_score == white_score) {
        // cout << "Egalité !" << endl;
        return 0; 
    } if(black_score < white_score) {
        // cout << "Victoire des [blancs] !" << endl; 
        return 1;        
    } else {
        // cout << "Victoire des <noirs> !" << endl;
        return -1;        
    }

}

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
    for(int i = 0; i<(int) board.size(); i++) {
        if(i % WIDTH == 0 && i != ((int) board.size() - 1)){
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
    for(int i=0; i<(int) board.size(); i++){
        if(!case_free(i) && board[i].getCouleur() == couleur){   
            vector<int> dep;    
            deplacementPossible(i, &dep);
            if(dep.size() > 0){
                return false;
            } 
        }
    }
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
    
    int arrivee = rand() % dep.size();
    arrivee = dep.at(arrivee);
    moves(position,arrivee);
}

vector<Hokito::Move> Hokito::get_moves(){
    vector<Move> res;
    for(int i=0; i<(int) board.size(); i++){
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
}

bool Hokito::end_of_game() {
    return noMoreMoves(tour);
}

int Hokito::current_player() const {
    if(tour) return 1;
    else return 0;
}

void Hokito::make_move(const Move& m) {
    moves(m.first, m.second);
}

void Hokito::playout(mt19937& engine) {
    while(!noMoreMoves(tour)) {
        if(tour) movesIA(1);
        else movesIA(0);
    }
}

string Hokito::player_to_string(int coul) const {
    if (coul== 1) return "[blancs]";
    else return "<noirs>";
}

ostream& operator<<(std::ostream& os, const Hokito& hokito) {
    hokito.print();
    return os;
}


ostream& operator<<(ostream& os, const Hokito::Move& move) {
    os << move.first << ", " << move.second << "\n";
    return os;
}

istream& operator>>(std::istream& is, Hokito::Move& m) { 
    is >> m.first >> m.second; return is; 
}

bool Hokito::end_of_game() {
    return noMoreMoves(tour);
}