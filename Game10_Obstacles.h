#ifndef GAME10_OBSTACLES_H
#define GAME10_OBSTACLES_H

#include "BoardGame_Classes.h"
#include <vector>

class Obstacles_Board : public Board<char> {
private:
    vector<pair<int,int>> obstacles;

public:
    Obstacles_Board() : Board<char>(6, 6) {
        for (auto& row : board)
            for (auto& cell : row) cell = ' ';
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        for (auto& obs : obstacles) {
            if (obs.first == x && obs.second == y) return false;
        }
        if (x < 0 || x >= 6 || y < 0 || y >= 6 || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol();
        n_moves++;

        if (n_moves % 2 == 0) {
            int added = 0;
            while (added < 2) {
                int rx = rand() % 6;
                int ry = rand() % 6;
                if (board[rx][ry] == ' ') {
                    obstacles.push_back({rx, ry});
                    added++;
                }
            }
        }
        return true;
    }

    bool is_win(Player<char>* player) override {
        char symbol = player->get_symbol();
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == symbol && board[i][j+1] == symbol &&
                    board[i][j+2] == symbol && board[i][j+3] == symbol) return true;
            }
        }
        return false;
    }

    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 6; j++) {
                bool isObstacle = false;
                for (auto& obs : obstacles) {
                    if (obs.first == i && obs.second == j) {
                        isObstacle = true;
                        break;
                    }
                }
                if (!isObstacle && board[i][j] == ' ') return false;
            }
        }
        return true;
    }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

class Obstacles_UI : public UI<char> {
public:
    Obstacles_UI() : UI<char>("Obstacles Tic-Tac-Toe", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        int x, y;
        cout << player->get_name() << ", enter row and column (0-5): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }
};

void runObstaclesGame() {
    srand(time(0));
    Obstacles_Board* board = new Obstacles_Board();
    Obstacles_UI* ui = new Obstacles_UI();

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