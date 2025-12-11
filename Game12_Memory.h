#ifndef GAME12_MEMORY_H
#define GAME12_MEMORY_H

#include "BoardGame_Classes.h"

class Memory_Board : public Board<char> {
private:
    char hiddenBoard[3][3];

public:
    Memory_Board() : Board<char>(3, 3) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = '?';
                hiddenBoard[i][j] = ' ';
            }
        }
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || hiddenBoard[x][y] != ' ') return false;
        hiddenBoard[x][y] = move->get_symbol();
        board[x][y] = move->get_symbol();
        n_moves++;

        // Hide the board after showing briefly
        cout << "\nBoard revealed for 2 seconds...\n";
        system("pause");
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (hiddenBoard[i][j] == ' ') board[i][j] = '?';

        return true;
    }

    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        for (int i = 0; i < 3; i++) {
            if (hiddenBoard[i][0] == symbol && hiddenBoard[i][1] == symbol && hiddenBoard[i][2] == symbol) return true;
            if (hiddenBoard[0][i] == symbol && hiddenBoard[1][i] == symbol && hiddenBoard[2][i] == symbol) return true;
        }
        if (hiddenBoard[0][0] == symbol && hiddenBoard[1][1] == symbol && hiddenBoard[2][2] == symbol) return true;
        if (hiddenBoard[0][2] == symbol && hiddenBoard[1][1] == symbol && hiddenBoard[2][0] == symbol) return true;
        return false;
    }

    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return n_moves == 9; }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

class Memory_UI : public UI<char> {
public:
    Memory_UI() : UI<char>("Memory Tic-Tac-Toe", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        cout << player->get_name() << ", enter row and column (0-2): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
};

void runMemoryGame() {
    Memory_Board* board = new Memory_Board();
    Memory_UI* ui = new Memory_UI();

    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();

    cout << "\nFinal revealed board:\n";
    vector<vector<char>> finalBoard(3, vector<char>(3));
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            finalBoard[i][j] = board->get_cell(i, j);
    ui->display_board_matrix(finalBoard);

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

#endif