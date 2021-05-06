#ifndef HOKITO_HPP
#define HOKITO_HPP

#include <iostream>
#include <array>
#include <vector>
#include <random>
#include "case.hpp"

using namespace std;

class Hokito {
    public:
        using Move = pair<int,int>;
        static const int WIN = 1;
        static const int LOST = -WIN;
        static const int WIDTH = 6;
        static const int HEIGHT = 6;
        static const int PIONS_BY_TYPE = 6;
        static const int PvP = 1;
        static const int PvIA = 2;
        static const int IAvIA = 3;

    private: 
        array<Case, WIDTH*HEIGHT> board{};
        bool tour;

    public:
        Hokito();
        inline bool case_free(const int position) const {
            return board[position].getPile() == 0;
        };
        int calculScore(bool couleur) const;
        int whoWins() const;
        inline bool won(int player) const {
            if(player == 1 && whoWins() == -1)
                return true;
            else if (player == 0 && whoWins() == 1)
                return true;
            return false;};
        inline bool value(int player) const {
            if(player == 1)
                return -whoWins();
            else if (player == 0)
                return whoWins();
            return false;
        };
        bool noMoreMoves(bool couleur);
        void moves(const int depart, const int arrivee);
        void movesIA(const int coul);
        void deplacementPossible(int depart, vector<int>* deplacement);
        void recDeplacement(const int position, const int valeur, const bool isPile, vector<int>* deplacement) const;
        void deplacementPossibleReel(const int position, const int valeur, vector<int>* deplacement, bool isPile) const;
        vector<Move> get_moves();
        void print() const;
        void play(int mode);
        bool end_of_game();
        int current_player();
        inline bool value_for_current_player(){ 
            return value(current_player());
        };
        void make_move(const Move& m);
        void playout(mt19937& engine);
        string player_to_string(int player) const;
};

ostream& operator<<(ostream& os, const Hokito& hokito);
ostream& operator<<(ostream& os, const Hokito::Move& move);
istream& operator>>(std::istream& is, Hokito::Move& m);

#endif 