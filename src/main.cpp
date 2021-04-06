#include "hokito.cpp"

int main(int argc, char *argv[])
{
    try
    {
        Hokito h = Hokito();
        int mode;
        cout << "Quel mode voulez-vous jouer ? (PvP : 1, PvIA : 2, IAvIA : 3) ";
        cin >> mode;
        h.play(mode);
    }
    catch (char const* e)
        {
        cout << e << endl;
        }
    return 0;
}