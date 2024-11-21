#include <gtkmm.h>
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

class TicTacToe : public Gtk::Window
{
public:
  TicTacToe();

private:
  Gtk::Grid grid;
  Gtk::Button buttons[3][3];
  char board[3][3];
  bool isPlayerTurn = true;

  void on_button_clicked(int row, int col);
  void ai_move();
  bool check_winner(char player);
  bool is_moves_left();
  int evaluate();
  int minimax(int depth, bool isAI);
  void reset_game();
  void update_ui();
};

TicTacToe::TicTacToe()
{
  set_title("Tic-Tac-Toe");
  set_default_size(300, 300);
  set_border_width(10);

  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      board[i][j] = ' ';
      buttons[i][j].set_label(" ");
      buttons[i][j].set_hexpand(true);
      buttons[i][j].set_vexpand(true);
      buttons[i][j].signal_clicked().connect(
          sigc::bind(sigc::mem_fun(*this, &TicTacToe::on_button_clicked), i, j));
      grid.attach(buttons[i][j], j, i, 1, 1);
    }
  }

  add(grid);
  show_all_children();
}

void TicTacToe::on_button_clicked(int row, int col)
{
  if (board[row][col] != ' ' || !isPlayerTurn)
    return;

  board[row][col] = 'X';
  isPlayerTurn = false;
  update_ui();

  if (check_winner('X'))
  {
    Gtk::MessageDialog dialog(*this, "You win!");
    dialog.run();
    reset_game();
    return;
  }

  if (is_moves_left())
  {
    ai_move();
    update_ui();

    if (check_winner('O'))
    {
      Gtk::MessageDialog dialog(*this, "AI wins!");
      dialog.run();
      reset_game();
      return;
    }
  }

  if (!is_moves_left())
  {
    Gtk::MessageDialog dialog(*this, "It's a draw!");
    dialog.run();
    reset_game();
  }
}

void TicTacToe::ai_move()
{
  int bestVal = -numeric_limits<int>::max();
  int bestRow = -1, bestCol = -1;

  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      if (board[i][j] == ' ')
      {
        board[i][j] = 'O';
        int moveVal = minimax(0, false);
        board[i][j] = ' ';
        if (moveVal > bestVal)
        {
          bestRow = i;
          bestCol = j;
          bestVal = moveVal;
        }
      }
    }
  }

  board[bestRow][bestCol] = 'O';
  isPlayerTurn = true;
}

bool TicTacToe::check_winner(char player)
{
  for (int i = 0; i < 3; ++i)
    if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
        (board[0][i] == player && board[1][i] == player && board[2][i] == player))
      return true;

  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
      (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    return true;

  return false;
}

bool TicTacToe::is_moves_left()
{
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      if (board[i][j] == ' ')
        return true;

  return false;
}

int TicTacToe::evaluate()
{
  if (check_winner('O'))
    return 10;
  if (check_winner('X'))
    return -10;
  return 0;
}

int TicTacToe::minimax(int depth, bool isAI)
{
  int score = evaluate();
  if (score == 10 || score == -10)
    return score;
  if (!is_moves_left())
    return 0;

  if (isAI)
  {
    int best = -numeric_limits<int>::max();
    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        if (board[i][j] == ' ')
        {
          board[i][j] = 'O';
          best = max(best, minimax(depth + 1, false));
          board[i][j] = ' ';
        }
      }
    }
    return best;
  }
  else
  {
    int best = numeric_limits<int>::max();
    for (int i = 0; i < 3; ++i)
    {
      for (int j = 0; j < 3; ++j)
      {
        if (board[i][j] == ' ')
        {
          board[i][j] = 'X';
          best = min(best, minimax(depth + 1, true));
          board[i][j] = ' ';
        }
      }
    }
    return best;
  }
}

void TicTacToe::reset_game()
{
  for (int i = 0; i < 3; ++i)
    for (int j = 0; j < 3; ++j)
      board[i][j] = ' ';

  isPlayerTurn = true;
  update_ui();
}

void TicTacToe::update_ui()
{
  for (int i = 0; i < 3; ++i)
  {
    for (int j = 0; j < 3; ++j)
    {
      if (board[i][j] == ' ')
        buttons[i][j].set_label(" ");
      else
        buttons[i][j].set_label(Glib::ustring(1, board[i][j]));
    }
  }
}

int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  TicTacToe game;
  return app->run(game);
}
