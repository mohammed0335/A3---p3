#ifndef _BOARDGAME_CLASSES_H
#define _BOARDGAME_CLASSES_H

#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
using namespace std;

template <typename T> class Player;
template <typename T> class Move;

enum class PlayerType { HUMAN, COMPUTER, AI, RANDOM };

template <typename T>
class Board {
protected:
    int rows, columns;
    vector<vector<T>> board;
    int n_moves = 0;
public:
    Board(int rows, int columns) : rows(rows), columns(columns),
        board(rows, vector<T>(columns)) {}
    virtual ~Board() {}
    virtual bool update_board(Move<T>* move) = 0;
    virtual bool is_win(Player<T>*) = 0;
    virtual bool is_lose(Player<T>*) = 0;
    virtual bool is_draw(Player<T>*) = 0;
    virtual bool game_is_over(Player<T>*) = 0;

    vector<vector<T>> get_board_matrix() const { return board; }
    int get_rows() const { return rows; }
    int get_columns() const { return columns; }
    int get_n_moves() const { return n_moves; }
    T get_cell(int x, int y) { return board[x][y]; }
};

template <typename T>
class Move {
    int x, y; T symbol;
public:
    Move(int x, int y, T symbol) : x(x), y(y), symbol(symbol) {}
    int get_x() const { return x; }
    int get_y() const { return y; }
    T get_symbol() const { return symbol; }
};

template <typename T>
class Player {
protected:
    string name; PlayerType type; T symbol; Board<T>* boardPtr;
public:
    Player(string n, T s, PlayerType t = PlayerType::HUMAN) :
        name(n), symbol(s), type(t), boardPtr(nullptr) {}
    virtual ~Player() {}

    virtual Move<T>* get_move() {
        return nullptr;
    }

    string get_name() const { return name; }
    PlayerType get_type() const { return type; }
    T get_symbol() const { return symbol; }
    Board<T>* get_board_ptr() const { return boardPtr; }
    void set_board_ptr(Board<T>* b) { boardPtr = b; }
};

template <typename T>
class UI {
protected:
    int cell_width;
public:
    UI(int cell_display_width = 3) : cell_width(cell_display_width) {}
    UI(string message, int cell_display_width) :
        cell_width(cell_display_width) { cout << message << endl; }
    virtual ~UI() {}
    virtual void display_message(string message) { cout << message << "\n"; }
    virtual Move<T>* get_move(Player<T>*) = 0;

    virtual Player<T>** setup_players() {
        Player<T>** players = new Player<T>*[2];

        string name1;
        cout << "\nEnter Player 1 name: ";
        getline(cin >> ws, name1);

        string name2;
        cout << "Enter Player 2 name: ";
        getline(cin >> ws, name2);

        players[0] = new Player<T>(name1, static_cast<T>('X'), PlayerType::HUMAN);
        players[1] = new Player<T>(name2, static_cast<T>('O'), PlayerType::HUMAN);

        return players;
    }

    virtual void display_board_matrix(const vector<vector<T>>& matrix) const {
        if (matrix.empty()) return;
        int rows = matrix.size(), cols = matrix[0].size();
        cout << "\n    ";
        for (int j = 0; j < cols; ++j) cout << setw(cell_width + 1) << j;
        cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        for (int i = 0; i < rows; ++i) {
            cout << setw(2) << i << " |";
            for (int j = 0; j < cols; ++j)
                cout << setw(cell_width) << matrix[i][j] << " |";
            cout << "\n   " << string((cell_width + 2) * cols, '-') << "\n";
        }
        cout << endl;
    }
};

template <typename T>
class GameManager {
    Board<T>* boardPtr; Player<T>* players[2]; UI<T>* ui;
public:
    GameManager(Board<T>* b, Player<T>* p[2], UI<T>* u) :
        boardPtr(b), ui(u) {
        players[0] = p[0]; players[1] = p[1];
        players[0]->set_board_ptr(b); players[1]->set_board_ptr(b);
    }
    void run() {
        ui->display_board_matrix(boardPtr->get_board_matrix());
        while (true) {
            for (int i : {0, 1}) {
                Move<T>* move = ui->get_move(players[i]);

                while (!boardPtr->update_board(move))
                    move = ui->get_move(players[i]);

                ui->display_board_matrix(boardPtr->get_board_matrix());

                if (boardPtr->is_win(players[i])) {
                    ui->display_message(players[i]->get_name() + " wins!");
                    return;
                }
                if (boardPtr->is_draw(players[i])) {
                    ui->display_message("Draw!");
                    return;
                }
            }
        }
    }
};

#endif