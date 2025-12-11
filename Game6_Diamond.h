#ifndef GAME6_DIAMOND_H
#define GAME6_DIAMOND_H

#include "BoardGame_Classes.h"

class Diamond_Board : public Board<char> {
private:
    bool diamondGrid[5][5] = {
        {false, false, true, false, false},
        {false, true, true, true, false},
        {true, true, true, true, true},
        {false, true, true, true, false},
        {false, false, true, false, false}
    };
public:
    Diamond_Board() : Board<char>(5, 5) {
        for (auto& row : board) for (auto& cell : row) cell = ' ';
    }
    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 5 || y < 0 || y >= 5 || !diamondGrid[x][y] || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol(); n_moves++; return true;
    }
    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        bool three = false, four = false;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 3; j++) {
                if (diamondGrid[i][j] && diamondGrid[i][j+1] && diamondGrid[i][j+2] &&
                    board[i][j] == symbol && board[i][j+1] == symbol && board[i][j+2] == symbol) three = true;
            }
        }
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 5; j++) {
                if (diamondGrid[i][j] && diamondGrid[i+1][j] && diamondGrid[i+2][j] && diamondGrid[i+3][j] &&
                    board[i][j] == symbol && board[i+1][j] == symbol && board[i+2][j] == symbol && board[i+3][j] == symbol) four = true;
            }
        } return three && four;
    }
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                if (diamondGrid[i][j] && board[i][j] == ' ') return false;
            }
        } return true;
    }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

class Diamond_UI : public UI<char> {
public:
    Diamond_UI() : UI<char>("Diamond Tic-Tac-Toe", 3) {}
    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        cout << player->get_name() << ", enter row and column (0-4): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
};

void runDiamondGame() {
    Diamond_Board* board = new Diamond_Board();
    Diamond_UI* ui = new Diamond_UI();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    delete board; delete ui; delete players[0]; delete players[1]; delete[] players;
}

#endif