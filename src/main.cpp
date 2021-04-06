#include "hokito.cpp"
using namespace std;

template <typename Game>
int move_to_index(const Game& g, const typename Game::Move& m)
{
  vector<typename Game::Move> moves = g.get_moves();
  int nb_moves = moves.size();
  for (int i = 0; i < nb_moves; ++i)
    {
      if (moves[i] == m) return i;
    }
  return -1;
}

template <typename Game>
int select_move(Game& g)
{
  cout << g.player_to_string(g.current_player()) << " move: ";
  vector<typename Game::Move> moves = g.get_moves();
  typename Game::Move m;
  cin >> m;
  int res = move_to_index(g, m);
  g.make_move(m);
  return res;
}

template <typename Game>
void play(Game g, int mode)
{
    int coul = Case::WHITE;
    int depart_ligne = 0;
    int depart_colonne = 0;
    int arrivee_ligne = 0;
    int arrivee_colonne = 0;
    if(mode == Hokito::PvIA){
        auto the_turk = make_mcts(g, 5000, 0.35, 4);
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
            else {   
                the_turk.last_moves(computer_last_move, human_last_move);
                typename Game::Move move = the_turk.select_move();
                computer_last_move = move_to_index(g, move);
                cout << g.player_to_string(g.current_player()) << " move: " << move << endl;
                g.make_move(move);
                movesIA(Case::BLACK);
            }
        }
    }
  
//   cout << "play one game" << std::endl;
//   cout << "who's first? (h)uman/(c)omputer ";
//   string ans;
//   getline(cin, ans);
//   cout << g << endl;
//   int human_last_move = -1, computer_last_move = -1;
  while (!g.end_of_game())
    {
      if ((ans == "h" && g.current_player() == 0) || (ans == "c" && g.current_player() == 1))
        {
          human_last_move = select_move(g);
        }
      else
        {
          if (human_last_move != -1 && computer_last_move != -1)
            {
              the_turk.last_moves(computer_last_move, human_last_move);
            }
          typename Game::Move move = the_turk.select_move();
          computer_last_move = move_to_index(g, move);
          cout << g.player_to_string(g.current_player()) << " move: " << move << endl;
          g.make_move(move);
        }
      cout << g << endl;
    }
  if (g.won(0)) cout << g.player_to_string(0) << " won";
  else if (g.won(1)) cout << g.player_to_string(1) << " won";
  else cout << "draw";
  cout << endl;
}


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