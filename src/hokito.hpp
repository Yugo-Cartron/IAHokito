#ifndef HOKITO_HPP
#define HOKITO_HPP

#include <iostream>
#include <array>
#include <vector>
#include <random>
#include "case.hpp"

class Hokito {

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
        int calculScore(bool couleur);
        int whoWins();
        bool noMoreMoves(bool couleur) const;
        void moves(const int depart, const int arrivee);
        void movesIA(const int coul);
        void deplacementPossible(const int position, const int valeur, std::vector<int>* deplacement) const;
        void deplacementPossibleReel(const int position, const int valeur, std::vector<int>* deplacement) const;
        void print() const;
        void play(int mode);
};

#endif 