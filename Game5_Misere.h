#ifndef GAME5_MISERE_H
#define GAME5_MISERE_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>

class Misere_AI_Player : public Player<char> {
public:
    Misere_AI_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_move() {
        Board<char>* board = this->get_board_ptr();
        vector<vector<char>> b = board->get_board_matrix();

        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(b[i][j] == ' ') {
                    cout << this->get_name() << " (AI) plays at (" << i << "," << j << ")" << endl;
                    return new Move<char>(i,j,this->get_symbol());
                }
            }
        }
        return new Move<char>(0,0,this->get_symbol());
    }
};

class Misere_Board : public Board<char> {
public:
    Misere_Board() : Board<char>(3, 3) {
        for (auto& row : board) for (auto& cell : row) cell = ' ';
    }
    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol(); n_moves++; return true;
    }
    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) return true;
            if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) return true;
        }
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) return true;
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) return true;
        return false;
    }
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return n_moves == 9 && !is_win(player); }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

class Misere_UI : public UI<char> {
public:
    Misere_UI() : UI<char>("Misere Tic Tac Toe", 3) {}
    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI) {
            Misere_AI_Player* aiPlayer = dynamic_cast<Misere_AI_Player*>(player);
            if (aiPlayer) {
                return aiPlayer->get_move();
            }
        }

        int x, y;
        cout << player->get_name() << ", enter row and column (0-2): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    Player<char>** setup_players() override {
        Player<char>** players = new Player<char>*[2];

        cout << "\n=== Misere Tic Tac Toe ===" << endl;
        cout << "In Misere, the player who makes 3 in a row LOSES!" << endl;

        cout << "\nChoose Player 1 type:" << endl;
        cout << "1. Human" << endl;
        cout << "2. AI Player" << endl;
        cout << "Choice: ";
        int choice1;
        cin >> choice1;

        string name1;
        cout << "\nEnter Player 1 name: ";
        getline(cin >> ws, name1);

        if (choice1 == 2) {
            players[0] = new Misere_AI_Player(name1, 'X');
        } else {
            players[0] = new Player<char>(name1, 'X', PlayerType::HUMAN);
        }

        cout << "\nChoose Player 2 type:" << endl;
        cout << "1. Human" << endl;
        cout << "2. AI Player" << endl;
        cout << "Choice: ";
        int choice2;
        cin >> choice2;

        string name2;
        cout << "\nEnter Player 2 name: ";
        getline(cin >> ws, name2);

        if (choice2 == 2) {
            players[1] = new Misere_AI_Player(name2, 'O');
        } else {
            players[1] = new Player<char>(name2, 'O', PlayerType::HUMAN);
        }

        cout << "\n" << name1 << " will use 'X'" << endl;
        cout << name2 << " will use 'O'" << endl;
        cout << "\nGame starting..." << endl;
        cout << "WARNING: In Misere, making 3 in a row makes you LOSE!" << endl;

        return players;
    }
};

void runMisereGame() {
    system("cls");
    Misere_Board* board = new Misere_Board();
    Misere_UI* ui = new Misere_UI();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    if (board->is_win(players[0]) || board->is_win(players[1]))
        ui->display_message("Player who made 3 in a row LOSES!");
    delete board; delete ui; delete players[0]; delete players[1]; delete[] players;
}

#endif