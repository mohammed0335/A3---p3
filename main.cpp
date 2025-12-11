#include <iostream>
#include <cstdlib>
#include <ctime>
#include "BoardGame_Classes.h"

// جميع includes للألعاب
#include "Game1_SUS.h"
#include "Game2_FourInRow.h"
#include "Game3_5x5TicTacToe.h"
#include "Game4_WordTicTacToe.h"
#include "Game5_Misere.h"
#include "Game6_Diamond.h"
#include "Game7_4x4TicTacToe.h"
#include "Game8_Pyramid.h"
#include "Game9_Numerical.h"
#include "Game10_Obstacles.h"
#include "Game11_Infinity.h"
#include "Game12_Memory.h"

using namespace std;

void displayMenu() {
    cout << "\n==========================================" << endl;
    cout << "       CS213 - Gaming App (Part 3)" << endl;
    cout << "==========================================" << endl;
    cout << "1. SUS Tic-Tac-Toe (Game 1)" << endl;
    cout << "2. Four-in-a-row (Game 2)" << endl;
    cout << "3. 5x5 Tic Tac Toe (Game 3)" << endl;
    cout << "4. Word Tic-tac-toe (Game 4)" << endl;
    cout << "5. Misere Tic Tac Toe (Game 5)" << endl;
    cout << "6. Diamond Tic-Tac-Toe (Game 6)" << endl;
    cout << "7. 4x4 Tic-Tac-Toe (Game 7)" << endl;
    cout << "8. Pyramid Tic-Tac-Toe (Game 8)" << endl;
    cout << "9. Numerical Tic-Tac-Toe (Game 9)" << endl;
    cout << "10. Obstacles Tic-Tac-Toe (Game 10)" << endl;
    cout << "11. Infinity Tic-Tac-Toe (Game 11)" << endl;
    cout << "12. Memory Tic-Tac-Toe (Game 12)" << endl;
    cout << "13. Exit" << endl;
    cout << "==========================================" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    int choice;

    cout << "Welcome to CS213 Gaming Application\n";
    cout << "Team: 20220621, 20220681, 20220791, 20220995\n";

    do {
        displayMenu();
        cout << "Enter choice (1-13): ";
        cin >> choice;

        switch(choice) {
            case 1: runSUSGame(); break;
            case 2: runFourInRowGame(); break;
            case 3: run5x5Game(); break;
            case 4: runWordGame(); break;
            case 5: runMisereGame(); break;
            case 6: runDiamondGame(); break;
            case 7: run4x4Game(); break;
            case 8: runPyramidGame(); break;
            case 9: runNumericalGame(); break;
            case 10: runObstaclesGame(); break;
            case 11: runInfinityGame(); break;
            case 12: runMemoryGame(); break;
            case 13: cout << "bye\n"; break;
            default: cout << "rong choice!\n";
        }

        if (choice != 13) {
            cout << "\nPress Enter to continue";
            cin.ignore();
            cin.get();
        }
    } while (choice = 13);

    return 0;
}