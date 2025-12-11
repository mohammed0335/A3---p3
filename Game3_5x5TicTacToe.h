#ifndef GAME3_5X5TICTACTOE_H
#define GAME3_5X5TICTACTOE_H

#include "BoardGame_Classes.h"

class FiveXFive_AI_Player : public Player<char> {
public:
    FiveXFive_AI_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_move() {
        Board<char>* board = this->get_board_ptr();
        vector<vector<char>> b = board->get_board_matrix();

        if(b[2][2] == ' ') {
            cout << this->get_name() << " (AI) plays at (2,2)" << endl;
            return new Move<char>(2,2,this->get_symbol());
        }

        vector<pair<int,int>> corners = {{0,0},{0,4},{4,0},{4,4}};
        for(auto corner : corners) {
            if(b[corner.first][corner.second] == ' ') {
                cout << this->get_name() << " (AI) plays at (" << corner.first << "," << corner.second << ")" << endl;
                return new Move<char>(corner.first,corner.second,this->get_symbol());
            }
        }

        for(int i=0;i<5;i++) {
            for(int j=0;j<5;j++) {
                if(b[i][j] == ' ') {
                    cout << this->get_name() << " (AI) plays at (" << i << "," << j << ")" << endl;
                    return new Move<char>(i,j,this->get_symbol());
                }
            }
        }

        return new Move<char>(0,0,this->get_symbol());
    }
};

class FiveXFive_Board : public Board<char> {
public:
    FiveXFive_Board() : Board<char>(5, 5) {
        for (auto& row : board) for (auto& cell : row) cell = ' ';
    }
    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 5 || y < 0 || y >= 5 || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol(); n_moves++; return true;
    }
    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol) return true;
            }
        }
        for (int j = 0; j < 5; j++) {
            for (int i = 0; i < 3; i++) {
                if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol) return true;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol) return true;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 2; j < 5; j++) {
                if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol) return true;
            }
        }
        return false;
    }
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return n_moves == 25; }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

class FiveXFive_UI : public UI<char> {
public:
    FiveXFive_UI() : UI<char>("5x5 Tic Tac Toe", 3) {}
    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI) {
            FiveXFive_AI_Player* aiPlayer = dynamic_cast<FiveXFive_AI_Player*>(player);
            if (aiPlayer) {
                return aiPlayer->get_move();
            }
        }

        int x, y;
        cout << player->get_name() << ", enter row and column (0-4): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    Player<char>** setup_players() override {
        Player<char>** players = new Player<char>*[2];

        cout << "\n=== 5x5 Tic Tac Toe ===" << endl;

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
            players[0] = new FiveXFive_AI_Player(name1, 'X');
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
            players[1] = new FiveXFive_AI_Player(name2, 'O');
        } else {
            players[1] = new Player<char>(name2, 'O', PlayerType::HUMAN);
        }

        cout << "\n" << name1 << " will use 'X'" << endl;
        cout << name2 << " will use 'O'" << endl;
        cout << "\nGame starting..." << endl;

        return players;
    }
};

void run5x5Game() {
    system("cls");
    FiveXFive_Board* board = new FiveXFive_Board();
    FiveXFive_UI* ui = new FiveXFive_UI();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    delete board; delete ui; delete players[0]; delete players[1]; delete[] players;
}

#endif