#include "hokito.cpp"

int main() {
    Hokito h = Hokito();
    int mode;
    cout << "Quel mode voulez-vous jouer ? (PvP : 1, PvIA : 2, IAvIA : 3) ";
    cin >> mode;
    h.play(mode);
}