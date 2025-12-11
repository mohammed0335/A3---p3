#ifndef GAME11_INFINITY_H
#define GAME11_INFINITY_H

#include "BoardGame_Classes.h"
#include <queue>

class Infinity_Board : public Board<char> {
private:
    queue<pair<int,int>> moveHistory;

public:
    Infinity_Board() : Board<char>(3, 3) {
        for (auto& row : board)
            for (auto& cell : row) cell = ' ';
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol();
        n_moves++;
        moveHistory.push({x, y});

        if (moveHistory.size() > 3) {
            auto old = moveHistory.front();
            board[old.first][old.second] = ' ';
            moveHistory.pop();
        }
        return true;
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
    bool is_draw(Player<char>* player) override { return false; }
    bool game_is_over(Player<char>* player) override { return is_win(player); }
};

class Infinity_UI : public UI<char> {
public:
    Infinity_UI() : UI<char>("Infinity Tic-Tac-Toe", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        cout << player->get_name() << ", enter row and column (0-2): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
};

void runInfinityGame() {
    Infinity_Board* board = new Infinity_Board();
    Infinity_UI* ui = new Infinity_UI();

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