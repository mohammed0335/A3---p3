#ifndef AI_PLAYERS_H
#define AI_PLAYERS_H

#include "BoardGame_Classes.h"
#include <vector>
#include <algorithm>
class SUS_AI_Player : public Player<char> {
public:
    SUS_AI_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_move() {
        Board<char>* board = this->get_board_ptr();
        vector<vector<char>> b = board->get_board_matrix();

        for(int i=0;i<3;i++) {
            for(int j=0;j<3;j++) {
                if(b[i][j] == ' ') {
                    cout<<this->get_name()<<" (AI) plays at ("<<i<<","<<j<<")"<<endl;
                    return new Move<char>(i,j,this->get_symbol());
                }
            }
        }
        return new Move<char>(0,0,this->get_symbol());
    }
};

class FourInRow_AI_Player : public Player<char> {
public:
    FourInRow_AI_Player(string name, char symbol) : Player<char>(name, symbol, PlayerType::AI) {}

    Move<char>* get_move() {
        Board<char>* board = this->get_board_ptr();
        vector<vector<char>> b = board->get_board_matrix();

        vector<int> cols = {3,2,4,1,5,0,6};

        for(int col:cols) {
            for(int row=5;row>=0;row--) {
                if(b[row][col] == ' ') {
                    cout<<this->get_name()<<" (AI) plays at column "<<col<<endl;
                    return new Move<char>(row,col,this->get_symbol());
                }
            }
        }
        return new Move<char>(0,0,this->get_symbol());
    }
};
 

#endif

