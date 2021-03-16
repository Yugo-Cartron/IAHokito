#include <iostream>
#include <array>
#include <random>

const int WIN = 1;
const int LOST = -WIN;

class Hokito {

    class Case{};
    public:
        static const int WIDTH = 6;
        static const int HEIGHT = 6;
        static const int PIONS_BY_TYPE = 6;

    private: 
        std::array<Case, WIDTH*HEIGHT> board;

    public:
        Hokito();
        int calculScore(bool couleur);

};