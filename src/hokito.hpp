#include <iostream>
#include <array>
#include <vector>
#include <random>
#include "case.hpp"

const int WIN = 1;
const int LOST = -WIN;

class Hokito {

    public:
        static const int WIDTH = 6;
        static const int HEIGHT = 6;
        static const int PIONS_BY_TYPE = 6;

    private: 
        std::array<Case, WIDTH*HEIGHT> board{};

    public:
        Hokito();
        int calculScore(bool couleur);
        int whoWins();
        std::vector<int> Hokito::deplacementPossible(const int position, const int valeur, std::vector<int> deplacement) const;

};