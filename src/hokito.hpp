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

    private: 
        std::array<Case, WIDTH*HEIGHT> board{};

    public:
        Hokito();
        int calculScore(bool couleur);
        int whoWins();
        std::vector<int> deplacementPossible(const int position, const int valeur, std::vector<int> deplacement) const;
        void print() const;

};

#endif 