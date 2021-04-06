#ifndef HOKITO_HPP
#define HOKITO_HPP

#include <iostream>
#include <array>
#include <vector>
#include <random>
#include "case.hpp"

class Hokito {
 
    public:
    using Move = pair<int, int>;
    bool end_of_game() const;
    bool won(int player) const;
    int value(int player) const;
    int current_player() const;
    void make_move(const Move& m);
    std::vector<Move> get_moves() const;
    void playout(std::mt19937& engine);
    std::string player_to_string(int player) const;
    

    public:
        static const int WIN = 1;
        static const int LOST = -WIN;
        static const int WIDTH = 6;
        static const int HEIGHT = 6;
        static const int PIONS_BY_TYPE = 6;
        static const int PvP = 1;
        static const int PvIA = 2;
        static const int IAvIA = 3;

    private: 
        std::array<Case, WIDTH*HEIGHT> board{};
        bool tour;

    public:
        Hokito();
        inline bool case_free(const int position) const {
            return board[position].getPile() == 0;
        };
        int calculScore(bool couleur) const;
        int whoWins() const;
        inline bool won(int player) const {return whoWins() == player;};
        bool noMoreMoves(bool couleur);
        void moves(const int depart, const int arrivee);
        void movesIA(const int coul);
        void deplacementPossible(int depart, std::vector<int>* deplacement);
        void recDeplacement(const int position, const int valeur, const bool isPile, std::vector<int>* deplacement) const;
        void deplacementPossibleReel(const int position, const int valeur, std::vector<int>* deplacement, bool isPile) const;
        void print() const;
        void play(int mode);
};

std::ostream& operator<<(std::ostream& os, const Hokito& hokito);

#endif 