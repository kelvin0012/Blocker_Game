#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class BlockerGame {
private:
    Board board;
public:
    // Play game
    void play();
};

void BlockerGame::play() {
    int cR, cC, bR, bC;
    int playerC = 1;
    int playerB = -1;
    int done = 0;

    // Randomise seed
    srand(time(NULL));

    // Get user inputs
    board.userBoardSize();
    board.userPlayerOption();

    // Printing the game board
    board.printGameBoard();

    while (done == 0)
    {
        // Adding player's moves
        board.addPlayerOption(cR, cC, bR, bC);

        board.addMoves(playerC, playerB, cR, cC, bR, bC);

        // Printing updated game board
        board.printGameBoard();

        // Returns game status for crosser wins and if the board is full
        done = board.gameStatus();
        if (done == 1)
            cout << "Crosser Wins!!" << endl;
        else if (done == -1)
            cout << "Blocker Wins!!" << endl;
    }
}