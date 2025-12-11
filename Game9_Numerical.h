#ifndef GAME9_NUMERICAL_H
#define GAME9_NUMERICAL_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>

class Numerical_Board : public Board<int> {
public:
    Numerical_Board() : Board<int>(3, 3) {
        for (auto& row : board)
            for (auto& cell : row) cell = 0;
    }

    bool update_board(Move<int>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != 0) return false;
        board[x][y] = move->get_symbol();
        n_moves++;
        return true;
    }

    bool is_win(Player<int>* player) override {
        for (int i = 0; i < 3; i++) {
            if (board[i][0] + board[i][1] + board[i][2] == 15 &&
                board[i][0] != 0 && board[i][1] != 0 && board[i][2] != 0) return true;
            if (board[0][i] + board[1][i] + board[2][i] == 15 &&
                board[0][i] != 0 && board[1][i] != 0 && board[2][i] != 0) return true;
        }
        if (board[0][0] + board[1][1] + board[2][2] == 15 &&
            board[0][0] != 0 && board[1][1] != 0 && board[2][2] != 0) return true;
        if (board[0][2] + board[1][1] + board[2][0] == 15 &&
            board[0][2] != 0 && board[1][1] != 0 && board[2][0] != 0) return true;
        return false;
    }

    bool is_lose(Player<int>* player) override { return false; }
    bool is_draw(Player<int>* player) override { return n_moves == 9; }
    bool game_is_over(Player<int>* player) override { return is_win(player) || is_draw(player); }
};

class Numerical_UI : public UI<int> {
private:
    vector<int> player1_nums = {1,3,5,7,9};
    vector<int> player2_nums = {2,4,6,8};
public:
    Numerical_UI() : UI<int>("Numerical Tic-Tac-Toe", 3) {}

    Move<int>* get_move(Player<int>* player) override {
        int x, y, num;
        cout << player->get_name() << ", enter row, column, and number: ";
        cin >> x >> y >> num;

        vector<int>* nums = (player->get_symbol() == 'X') ? &player1_nums : &player2_nums;
        auto it = find(nums->begin(), nums->end(), num);
        if (it != nums->end()) {
            nums->erase(it);
            return new Move<int>(x, y, num);
        } else {
            cout << "Invalid number! Available: ";
            for (int n : *nums) cout << n << " ";
            cout << endl;
            return get_move(player);
        }
    }

    void display_board_matrix(const vector<vector<int>>& matrix) const override {
        if (matrix.empty()) return;
        int rows = matrix.size();
        int cols = matrix[0].size();

        cout << "\n    ";
        for (int j = 0; j < cols; ++j)
            cout << setw(cell_width + 1) << j;
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";

        for (int i = 0; i < rows; ++i) {
            cout << setw(2) << i << " |";
            for (int j = 0; j < cols; ++j) {
                if (matrix[i][j] == 0) cout << setw(cell_width) << "." << " |";
                else cout << setw(cell_width) << matrix[i][j] << " |";
            }
            cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        }
        cout << endl;
    }
};

void runNumericalGame() {
    Numerical_Board* board = new Numerical_Board();
    Numerical_UI* ui = new Numerical_UI();

    Player<int>** players = new Player<int>*[2];
    players[0] = new Player<int>("Player1 (odds)", 'X');
    players[1] = new Player<int>("Player2 (evens)", 'O');

    GameManager<int> game(board, players, ui);
    game.run();

    delete board;
    delete ui;
    delete players[0];
    delete players[1];
    delete[] players;
}

#endif