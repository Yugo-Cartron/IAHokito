#include "hokito.hpp"
#include "mcts.hpp"

using namespace std;

template <typename Game>
int move_to_index(Game& g, const typename Game::Move& m)
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
void play(Game g)
{
  auto the_turk = make_mcts(g, 5000, 0.35, 4);
  cout << "play one game" << std::endl;
  cout << "who's first? (h)uman/(c)omputer ";
  string ans;
  getline(cin, ans);
  cout << g << endl;
  int human_last_move = -1, computer_last_move = -1;
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
      play(Hokito());
    }
  catch (char const* e)
    {
      cout << e << endl;
    }
  return 0;
}
