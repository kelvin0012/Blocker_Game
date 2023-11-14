#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
class Board {
private:
    int **gameBoard;
    int boardSize;
    int noOfMoves;
    // User options
    int option;
    // Straight Line Player
    int rowC, rowB;
    int colC = 1;
    int colB = 1;
    bool needNewLineC = true;
    bool needNewLineB = true;
    // Check Crosser Wins
    int **table;
    int row, col;
public:
    // Default constructor
    Board() {   
        gameBoard = new int*[boardSize];
        for (int i = 0; i < boardSize; i++)
            gameBoard[i] = new int[boardSize];
        
        table = new int*[boardSize];
        for (int i = 0; i < boardSize; i++)
            table[i] = new int[boardSize];

        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
            {
                table[i][j] = 0;
                gameBoard[i][j] = 0;
            }
        noOfMoves = 0;   
    }

    //Copy constructor
    Board(const Board& cboard) {
        for (int i = 0; i < boardSize; i++)
            for (int j = 0; j < boardSize; j++)
                gameBoard[i][j] = cboard.gameBoard[i][j];
        noOfMoves = cboard.noOfMoves;
    }

    // Destructor
    ~Board() {
        for (int i = 0; i < boardSize; i++)
        {
            delete[] table[i];
            delete[] gameBoard[i];
        }
        delete[] table;
        delete[] gameBoard;
    }
    
    // User Inputs
    void userBoardSize();
    void userPlayerOption();
    void addPlayerOption(int&, int&, int&, int&);
    // Human Players
    void humanPlayerCrosser(int&, int&);
    void humanPlayerBlocker(int&, int&);
    // Random Players
    void randomPlayerBlocker(int&, int&);
    void randomPlayerCrosser(int&, int&);
    // Straight Line Players
    void straightLinePlayerCrosser(int&, int&);
    void straightLinePlayerBlocker(int&, int&);
    // Validate Moves
    bool checkMoveCrosser(int, int);
    bool checkMoveBlocker(int, int);
    void addMoves(int, int, int, int, int, int);
    // Board functions
    void playBoard();
    void printGameBoard();
    // Checking wins and board full
    void checkCellPath();
    int checkCrosserWin();
    int checkBoardFull();
    int gameStatus();
};

// Get input of boardsize
void Board::userBoardSize() {
    do
    {
        cout << "Input board size: ";
        cin >> boardSize;
    } while (boardSize < 3 || boardSize > 15);
}

// Get input of options
void Board::userPlayerOption() {
    cout << "Choose a option: \n"
         << "1. Human Player vs Random Player. \n"
         << "2. Straight Line Player vs Random Player. \n"
         << "3. Human Player vs Straight Line Player. \n"
         << "4. Human Player vs Human Player. \n"
         << "5. Random Player vs Random Player. \n"
         << "6. Straight Line Player vs Straight Line Player." << endl;
    do {
        cin >> option;
    } while (option < 1 || option > 6 );
}

void Board::addPlayerOption(int& cR, int& cC, int& bR, int& bC) {
     switch (option)
        {
        case 1:
            humanPlayerCrosser(cR, cC);
            randomPlayerBlocker(bR, bC);
            break;
        case 2:
            straightLinePlayerCrosser(cR, cC);
            randomPlayerBlocker(bR, bC);
            break;
        case 3:
            humanPlayerCrosser(cR, cC);
            straightLinePlayerBlocker(bR, bC);
            break;
        case 4:
            humanPlayerCrosser(cR, cC);
            humanPlayerBlocker(bR, bC);
            break;
        case 5:
            randomPlayerCrosser(cR, cC);
            randomPlayerBlocker(bR, bC);
            break;
        case 6:
            straightLinePlayerCrosser(cR, cC);
            straightLinePlayerBlocker(bR, bC);
            break;
        };
}

// Human player moves for crosser
void Board::humanPlayerCrosser(int& cR, int& cC) {
    int cRow, cCol;
    cout << "Enter Crosser's Move: ";
    do {    
        cin >> cRow >> cCol;
    } while(!checkMoveCrosser(cRow - 1, cCol - 1));
    cR = cRow - 1;
    cC = cCol - 1;
}

// Human player moves for blocker
void Board::humanPlayerBlocker(int& bR, int& bC) {
    int bRow, bCol;
    cout << "Enter Blocker's Move: ";
    do {
        cin >> bRow >> bCol;
    } while(!checkMoveBlocker(bRow -1, bCol - 1));
    bR = bRow - 1;
    bC = bCol - 1;
}

// Random player crosser moves
void Board::randomPlayerCrosser(int& cR, int& cC) {
    int cRow, cCol;
    cout << "Random Player inputting moves..." << endl;
    do { 
        cRow = rand() % boardSize + 1;
        cCol = rand() % boardSize + 1;
    } while(!checkMoveBlocker(cRow -1, cCol - 1));
    cR = cRow - 1;
    cC = cCol - 1;
}

// Random player blocker moves
void Board::randomPlayerBlocker(int& bR, int& bC) {
    int bRow, bCol;
    cout << "Random Player inputting moves..." << endl;
    do { 
        bRow = rand() % boardSize + 1;
        bCol = rand() % boardSize + 1;
    } while(!checkMoveBlocker(bRow -1, bCol - 1));
    bR = bRow - 1;
    bC = bCol - 1;
}

// Straight line player crosser moves
void Board::straightLinePlayerCrosser(int& cR, int& cC) {
    int cRow, cCol;
    cout << "Straightline Player inputting moves..." << endl;
    do {    
        if (needNewLineC == true)
        {
            rowC = rand() % boardSize + 1;
            cRow = rowC;
        }
        needNewLineC = false;

        if (colC <= boardSize + 1)
        {
            cRow = rowC;
            cCol = colC;
            colC += 1;
        }
        else
        {
            needNewLineC = true;
            colC = 1;
        }
    } while(!checkMoveCrosser(cRow - 1, cCol - 1));
    cR = cRow - 1;
    cC = cCol - 1;
}

// Straight line player blocker moves
void Board::straightLinePlayerBlocker(int& bR, int& bC) {
    int bRow, bCol;
    cout << "Straightline Player inputting moves..." << endl;
    do {    
        if (needNewLineB == true)
        {   
            colB = rand() % boardSize + 1;
            bCol = colB;
        }
        needNewLineB = false;

        if (rowB <= boardSize + 1)
        {
            bRow = rowB;
            bCol = colB;
            rowB += 1;
        }
        else
        {
            needNewLineB = true;
            rowB = 1;
        }
    } while(!checkMoveCrosser(bRow - 1, bCol - 1));
    bR = bRow - 1;
    bC = bCol - 1;
}

// Checking moves of the crosser 
bool Board::checkMoveCrosser(int cRow, int cCol) {
    if ((cRow > -1 && cRow < boardSize && cCol > -1 && cCol < boardSize ) && (gameBoard[cRow][cCol] != 1 && gameBoard[cRow][cCol] != -1))
        return true;
    else
        return false;
}

// Checking moves of the blocker
bool Board::checkMoveBlocker(int bRow, int bCol) {
    if ((bRow > -1 && bRow < boardSize && bCol > -1 && bCol < boardSize) && (gameBoard[bRow][bCol] != 1 && gameBoard[bRow][bCol] != -1))
        return true;
    else
        return false;
}

// Add moves to the game board
void Board::addMoves(int playerC, int playerB,int cR, int cC, int bR, int bC) {
    if (cR == bR && cC == bC)
    {
        gameBoard[bR][bC] = playerB;
        noOfMoves += 1;
    }
    else
    {
        gameBoard[cR][cC] = playerC;
        gameBoard[bR][bC] = playerB;
        noOfMoves += 2;
    }
}

// Display game board
void Board::printGameBoard() {
    cout << "   ";
    for (int i = 0; i < boardSize; i++)
    {
        if (i >= 9)
            cout << "  " << i + 1;
        else
            cout << "  " << i + 1 << " ";
    }
    cout << endl;

    cout << "   ";
    for (int i = 1; i <= boardSize; i++)
    {
        if (i == 1)
            cout << "-----";
        else
            cout << "----";
        
    }
    cout << endl;

    for (int i = 0; i < boardSize; i++)
    {   
        if (i >= 9)
            cout << i + 1 << " |";
        else
            cout << " " << i + 1 << " |";

        for (int j = 0; j < boardSize; j++)
        {
            char playerSymbol = ' ';
            if (gameBoard[i][j] == 1)
                playerSymbol = 'C';
            else if (gameBoard[i][j] == -1)
                playerSymbol = 'B';
            cout << setw(2) << playerSymbol << " |";
        }
        if (i != boardSize - 1)
            cout << endl << endl;
        else
            cout << endl;
    }

    cout << "   ";
    for (int i = 1; i <= boardSize; i++)
    {
        if (i == 1)
            cout << "-----";
        else
            cout << "----";
        
    }
    cout << endl;
}

void Board::checkCellPath() {
    if (row != 0) // up
        if (gameBoard[row-1][col] == 1)
            table[row-1][col] = 1;
 
    if (row != (boardSize - 1)) // down
        if (gameBoard[row+1][col] == 1)
            table[row+1][col] = 1;
    
    if (col != (boardSize - 1)) // right
        if (gameBoard[row][col+1] == 1)
            table[row][col+1] = 1;

    if (row !=0 && col != (boardSize - 1)) // up-right
        if (gameBoard[row-1][col+1] == 1)
            table[row-1][col+1] = 1;
    
    if (row != (boardSize - 1) && col != (boardSize - 1)) // down-right
        if (gameBoard[row+1][col+1] == 1)
            table[row+1][col+1] = 1;
}


int Board::checkCrosserWin() {
    // Check the cells path if there is a crosser symbol 
    for (int j = 0; j < boardSize; j++)
        for (int i = 0; i < boardSize; i++)
        {
            if (gameBoard[i][0] == 1)
                table[i][0] = gameBoard[i][0];

            if (table[i][j] == 1)
            {
                row = i;
                col = j;
                checkCellPath();
            }
        }

    // Check last column for a win
    for (int i = 0; i < boardSize; i++)
        if (table[i][boardSize-1] == 1)
            return 1;
    return 0;
}

// Check if board is full
int Board::checkBoardFull() {
    if (noOfMoves >= boardSize*boardSize)
        return -1;
    else
        return 0;
}

// Returns the current game status
int Board::gameStatus() {
    if (checkCrosserWin() == 1)
        return 1;
    else if (checkBoardFull() == -1)
        return -1;
    return 0;
}