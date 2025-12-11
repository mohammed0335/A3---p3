#ifndef GAME4_WORDTICTACTOE_H
#define GAME4_WORDTICTACTOE_H

#include "BoardGame_Classes.h"
#include <fstream>
#include <vector>
#include <algorithm>

vector<string> dictionary;

void loadDictionary() {
    ifstream file("dic.txt");
    string word;
    while (file >> word) dictionary.push_back(word);
    file.close();
}

class WordTicTacToe_AI_Player : public Player<char> {
public:
    WordTicTacToe_AI_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_move() {
        Board<char>* board = this->get_board_ptr();
        vector<vector<char>> b = board->get_board_matrix();

        // محاولة إيجاد حركة تصنع كلمة
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(b[i][j] == ' ') {
                    // تجربة أحرف مختلفة
                    for(char letter='A'; letter<='Z'; letter++) {
                        // تحقق إذا كانت الحركة ستكون صحيحة
                        if(isValidMove(i,j,letter)) {
                            cout << this->get_name() << " (AI) plays at (" << i << "," << j << ") with letter '" << letter << "'" << endl;
                            return new Move<char>(i,j,letter);
                        }
                    }
                }
            }
        }

        // إذا لم يجد كلمة، حركة عشوائية
        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(b[i][j] == ' ') {
                    char randomLetter = 'A' + rand() % 26;
                    cout << this->get_name() << " (AI) plays at (" << i << "," << j << ") with letter '" << randomLetter << "'" << endl;
                    return new Move<char>(i,j,randomLetter);
                }
            }
        }

        return new Move<char>(0,0,'A');
    }

private:
    bool isValidMove(int x, int y, char letter) {
        // دالة بسيطة للتحقق من صحة الحركة
        return true; // في الواقع تحتاج تحقق من القاموس
    }
};

class WordTicTacToe_Board : public Board<char> {
public:
    WordTicTacToe_Board() : Board<char>(3, 3) {
        for (auto& row : board) for (auto& cell : row) cell = ' ';
        loadDictionary();
    }
    bool update_board(Move<char>* move) override {
        int x = move->get_x(), y = move->get_y();
        if (x < 0 || x >= 3 || y < 0 || y >= 3 || board[x][y] != ' ') return false;
        board[x][y] = move->get_symbol(); n_moves++; return true;
    }
    bool is_win(Player<char>* player) override {
        for (int i = 0; i < 3; i++) {
            string row, col;
            for (int j = 0; j < 3; j++) {
                row += board[i][j];
                col += board[j][i];
            }
            if (find(dictionary.begin(), dictionary.end(), row) != dictionary.end() && row != "   ") return true;
            if (find(dictionary.begin(), dictionary.end(), col) != dictionary.end() && col != "   ") return true;
        }
        string diag1, diag2;
        diag1 += board[0][0]; diag1 += board[1][1]; diag1 += board[2][2];
        diag2 += board[0][2]; diag2 += board[1][1]; diag2 += board[2][0];
        if (find(dictionary.begin(), dictionary.end(), diag1) != dictionary.end() && diag1 != "   ") return true;
        if (find(dictionary.begin(), dictionary.end(), diag2) != dictionary.end() && diag2 != "   ") return true;
        return false;
    }
    bool is_lose(Player<char>* player) override { return false; }
    bool is_draw(Player<char>* player) override { return n_moves == 9; }
    bool game_is_over(Player<char>* player) override { return is_win(player) || is_draw(player); }
};

class WordTicTacToe_UI : public UI<char> {
public:
    WordTicTacToe_UI() : UI<char>("Word Tic-Tac-Toe", 3) {}
    Move<char>* get_move(Player<char>* player) override {
        if (player->get_type() == PlayerType::AI) {
            WordTicTacToe_AI_Player* aiPlayer = dynamic_cast<WordTicTacToe_AI_Player*>(player);
            if (aiPlayer) {
                return aiPlayer->get_move();
            }
        }

        int x, y; char letter;
        cout << player->get_name() << ", enter row, column, and letter (0-2): ";
        cin >> x >> y >> letter;
        return new Move<char>(x, y, letter);
    }

    Player<char>** setup_players() override {
        Player<char>** players = new Player<char>*[2];

        cout << "\n=== Word Tic-Tac-Toe ===" << endl;
        cout << "Form 3-letter words from the dictionary to win!" << endl;

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
            players[0] = new WordTicTacToe_AI_Player(name1, ' ');
        } else {
            players[0] = new Player<char>(name1, ' ', PlayerType::HUMAN);
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
            players[1] = new WordTicTacToe_AI_Player(name2, ' ');
        } else {
            players[1] = new Player<char>(name2, ' ', PlayerType::HUMAN);
        }

        cout << "\n" << name1 << " vs " << name2 << endl;
        cout << "\nGame starting..." << endl;

        return players;
    }
};

void runWordGame() {
    system("cls");
    WordTicTacToe_Board* board = new WordTicTacToe_Board();
    WordTicTacToe_UI* ui = new WordTicTacToe_UI();
    Player<char>** players = ui->setup_players();
    GameManager<char> game(board, players, ui);
    game.run();
    delete board; delete ui; delete players[0]; delete players[1]; delete[] players;
}

#endif