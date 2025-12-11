#ifndef GAME1_SUS_H
#define GAME1_SUS_H

#include "BoardGame_Classes.h"
#include "AI_Players.h"  // تضمين AI_Players.h هنا

class SUS_Board : public Board<char> {
public:
    SUS_Board() : Board<char>(3, 3) {
        for (auto& row : board) for (auto& cell : row) cell = ' ';
    }

    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol();
        n_moves++;
        return true;
    }

    bool is_win(Player<char>* player) override { return false; }
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return n_moves == 9; }
    bool game_is_over(Player<char>* player) override { return is_draw(player); }
};

class SUS_UI : public UI<char> {
public:
    SUS_UI() : UI<char>("SUS Tic-Tac-Toe", 3) {}

    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI) {
            SUS_AI_Player* aiPlayer = dynamic_cast<SUS_AI_Player*>(player);
            if (aiPlayer) {
                return aiPlayer->get_move();
            }
        }

        int x, y;
        cout << "\n" << player->get_name() << ", enter row and column (0-2): ";
        cin >> x >> y;
        return new Move<char>(x, y, player->get_symbol());
    }

    Player<char>** setup_players() override {
        Player<char>** players = new Player<char>*[2];

        cout << "\n=== SUS Tic-Tac-Toe ===" << endl;
        cout << "Player 1 uses 'S', Player 2 uses 'U'" << endl;

        cout << "\nChoose Player 1 (uses S) type:" << endl;
        cout << "1. Human" << endl;
        cout << "2. AI Player" << endl;
        cout << "Choice: ";
        int choice1;
        cin >> choice1;

        string name1;
        cout << "\nEnter Player 1 name: ";
        getline(cin >> ws, name1);

        if (choice1 == 2) {
            players[0] = new SUS_AI_Player(name1, 'S');
        } else {
            players[0] = new Player<char>(name1, 'S', PlayerType::HUMAN);
        }

        cout << "\nChoose Player 2 (uses U) type:" << endl;
        cout << "1. Human" << endl;
        cout << "2. AI Player" << endl;
        cout << "Choice: ";
        int choice2;
        cin >> choice2;

        string name2;
        cout << "\nEnter Player 2 name: ";
        getline(cin >> ws, name2);

        if (choice2 == 2) {
            players[1] = new SUS_AI_Player(name2, 'U');
        } else {
            players[1] = new Player<char>(name2, 'U', PlayerType::HUMAN);
        }

        cout << "\n" << name1 << " will use 'S'" << endl;
        cout << name2 << " will use 'U'" << endl;
        cout << "\nGame starting..." << endl;

        return players;
    }
};

void runSUSGame() {
    system("cls");
    SUS_Board* board = new SUS_Board();
    SUS_UI* ui = new SUS_UI();

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