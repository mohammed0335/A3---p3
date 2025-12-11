#ifndef GAME2_FOURINROW_H
#define GAME2_FOURINROW_H

#include "BoardGame_Classes.h"
#include "AI_Players.h"

class FourInRow_Board : public Board<char> {
public:
    FourInRow_Board() : Board<char>(6, 7) {
        for (auto& row : board) for (auto& cell : row) cell = ' ';
    }

    bool update_board(Move<char>* move) override {
        int y = move->get_y();
        if (y < 0 || y >= 7) return false;

        for (int i = 5; i >= 0; i--) {
            if (board[i][y] == ' ') {
                board[i][y] = move->get_symbol();
                n_moves++;
                return true;
            }
        }
        return false;
    }

    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i][j+1] == symbol &&
                    board[i][j+2] == symbol && board[i][j+3] == symbol) return true;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 7; j++) {
                if (board[i][j] == symbol && board[i+1][j] == symbol &&
                    board[i+2][j] == symbol && board[i+3][j] == symbol) return true;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i+1][j+1] == symbol &&
                    board[i+2][j+2] == symbol && board[i+3][j+3] == symbol) return true;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 3; j < 7; j++) {
                if (board[i][j] == symbol && board[i+1][j-1] == symbol &&
                    board[i+2][j-2] == symbol && board[i+3][j-3] == symbol) return true;
            }
        }
        return false;
    }

    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return n_moves == 42; }
    bool game_is_over(Player<char>* player) override {
        return is_win(player) || is_draw(player);
    }
};

class FourInRow_UI : public UI<char> {
public:
    FourInRow_UI() : UI<char>("Four-in-a-row", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        // إذا كان اللاعب AI، استدعاء get_move الخاص به
        if (player->get_type() == PlayerType::AI) {
            FourInRow_AI_Player* aiPlayer = dynamic_cast<FourInRow_AI_Player*>(player);
            if (aiPlayer) {
                return aiPlayer->get_move();
            }
        }

        // إذا كان لاعب بشري
        int y;
        cout << "\n" << player->get_name() << ", enter column (0-6): ";
        cin >> y;
        return new Move<char>(0, y, player->get_symbol());
    }

    Player<char>** setup_players() override {
        Player<char>** players = new Player<char>*[2];

        cout << "\n=== Four-in-a-row Game ===" << endl;
        cout << "Connect 4 pieces vertically, horizontally or diagonally to win!" << endl;

        cout << "\nChoose Player 1 (uses X) type:" << endl;
        cout << "1. Human" << endl;
        cout << "2. AI Player" << endl;
        cout << "Choice: ";
        int choice1;
        cin >> choice1;

        string name1;
        cout << "\nEnter Player 1 name: ";
        getline(cin >> ws, name1);

        if (choice1 == 2) {
            players[0] = new FourInRow_AI_Player(name1, 'X');
        } else {
            players[0] = new Player<char>(name1, 'X', PlayerType::HUMAN);
        }

        cout << "\nChoose Player 2 (uses O) type:" << endl;
        cout << "1. Human" << endl;
        cout << "2. AI Player" << endl;
        cout << "Choice: ";
        int choice2;
        cin >> choice2;

        string name2;
        cout << "\nEnter Player 2 name: ";
        getline(cin >> ws, name2);

        if (choice2 == 2) {
            players[1] = new FourInRow_AI_Player(name2, 'O');
        } else {
            players[1] = new Player<char>(name2, 'O', PlayerType::HUMAN);
        }

        cout << "\n" << name1 << " will use 'X'" << endl;
        cout << name2 << " will use 'O'" << endl;
        cout << "\nGame starting..." << endl;

        return players;
    }
};

void runFourInRowGame() {
    system("cls");
    FourInRow_Board* board = new FourInRow_Board();
    FourInRow_UI* ui = new FourInRow_UI();

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