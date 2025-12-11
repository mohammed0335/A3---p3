#ifndef GAME7_4X4TICTACTOE_H
#define GAME7_4X4TICTACTOE_H

#include "BoardGame_Classes.h"

class FourXFour_AI_Player : public Player<char> {
public:
    FourXFour_AI_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_move() {
        Board<char>* board = this->get_board_ptr();
        vector<vector<char>> b = board->get_board_matrix();


        if(b[1][1] == ' ') {
            cout << this->get_name() << " (AI) plays at (1,1)" << endl;
            return new Move<char>(1,1,this->get_symbol());
        }


        for(int i=0;i<4;i++) {
            for(int j=0;j<4;j++) {
                if(b[i][j] == ' ') {
                    cout << this->get_name() << " (AI) plays at (" << i << "," << j << ")" << endl;
                    return new Move<char>(i,j,this->get_symbol());
                }
            }
        }
        return new Move<char>(0,0,this->get_symbol());
    }
};

class FourXFour_Board : public Board<char> {
public:
    FourXFour_Board() : Board<char>(4, 4) {
        for (auto& row : board) for (auto& cell : row) cell = ' ';
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 4 || y < 0 || y >= 4 || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol();
        n_moves++;
        return true;
    }

    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 2; j++) {
                if (board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol) return true;
            }
        }
        for (int j = 0; j < 4; j++) {
            for (int i = 0; i < 2; i++) {
                if (board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol) return true;
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                if (board[i][j] == symbol && board[i+1][j+1] == symbol && board[i+2][j+2] == symbol) return true;
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 2; j < 4; j++) {
                if (board[i][j] == symbol && board[i+1][j-1] == symbol && board[i+2][j-2] == symbol) return true;
            }
        }
        return false;
    }

    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return n_moves == 16; }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

class FourXFour_UI : public UI<char> {
public:
    FourXFour_UI() : UI<char>("4x4 Tic-Tac-Toe", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI) {
            FourXFour_AI_Player* aiPlayer = dynamic_cast<FourXFour_AI_Player*>(player);
            if (aiPlayer) {
                return aiPlayer->get_move();
            }
        }

        int x, y;
        cout << player->get_name() << ", enter row and column (0-3): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    Player<char>** setup_players() override {
        Player<char>** players = new Player<char>*[2];

        cout << "\n= 4x4 Tic-Tac-Toe ==" << endl;
        cout << "Connect 3 in a row to win" << endl;

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
            players[0] = new FourXFour_AI_Player(name1, 'X');
        } else {
            players[0] = new Player<char>(name1, 'X', PlayerType::HUMAN);
        }

        cout << "\nChoose Player 2 type" << endl;
        cout << "1. Human" << endl;
        cout << "2. AI Player" << endl;
        cout << "Choice: ";
        int choice2;
        cin >> choice2;

        string name2;
        cout << "\nenter Player 2 name: ";
        getline(cin >> ws, name2);

        if (choice2 == 2) {
            players[1] = new FourXFour_AI_Player(name2, 'O');
        } else {
            players[1] = new Player<char>(name2, 'O', PlayerType::HUMAN);
        }

        cout << "\n" << name1 << " will use 'X'" << endl;
        cout << name2 << " will use 'O'" << endl;
        cout << "\nGame starting" << endl;

        return players;
    }
};

void run4x4Game() {
    system("cls");
    FourXFour_Board* board = new FourXFour_Board();
    FourXFour_UI* ui = new FourXFour_UI();

    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}


#endif
