#include <iostream>
#include <climits>
#include <time.h>

const int SIZE = 5;
const int winSize = 4;
const int EMPTY = 0;
const int PLAYER = 1;
const int COMPUTER = 2;


// Function to print the Tic-Tac-Toe board
void printBoard(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY)
                std::cout << "-";
            else if (board[i][j] == PLAYER)
                std::cout << "X";
            else if (board[i][j] == COMPUTER)
                std::cout << "O";
                std::cout << " ";
        }
        std::cout << std::endl;
    }
}

// Function to check if the board is full
bool isBoardFull(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY)
                return false;
        }
    }
    return true;
}

// Function to check if a player has won
/*bool hasPlayerWon(int board[SIZE][SIZE], int player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; i++) {
        bool rowWin = true;
        bool colWin = true;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != player) {
                rowWin = false;
            }
            if (board[j][i] != player) {
                colWin = false;
            }
        }
        if (rowWin || colWin) {
            return true;
        }
    }

    // Check diagonals
    bool diagWin1 = true;
    bool diagWin2 = true;
    for (int i = 0; i < SIZE; i++) {
        if (board[i][i] != player) {
            diagWin1 = false;
        }
        if (board[i][SIZE - i - 1] != player) {
            diagWin2 = false;
        }
    }
    if (diagWin1 || diagWin2) {
        return true;
    }

    return false;
}*/

bool hasPlayerWon(int board[SIZE][SIZE], int PLAYER) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        int count = 0;
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == PLAYER)
                count++;
            else
                count = 0;

            if (count == winSize)
                return true;
        }
    }

    // Check columns
    for (int j = 0; j < SIZE; j++) {
        int count = 0;
        for (int i = 0; i < SIZE; i++) {
            if (board[i][j] == PLAYER)
                count++;
            else
                count = 0;

            if (count == winSize)
                return true;
        }
    }

    // Check diagonals
    for (int i = 0; i <= SIZE - winSize; i++) {
        for (int j = 0; j <= SIZE - winSize; j++) {
            bool diagonal1 = true;
            bool diagonal2 = true;

            for (int k = 0; k < winSize; k++) {
                if (board[i + k][j + k] != PLAYER)
                    diagonal1 = false;

                if (board[i + k][j + winSize - 1 - k] != PLAYER)
                    diagonal2 = false;
            }

            if (diagonal1 || diagonal2)
                return true;
        }
    }

    return false;
}

// Function to evaluate the score of the board
int evaluateBoard(int board[SIZE][SIZE], int PLAYER) {
    if (hasPlayerWon(board, PLAYER))
        return 10;
    else if (hasPlayerWon(board, COMPUTER))
        return -10;
    else
        return 0;
}

// Function to implement the minimax algorithm with alpha-beta pruning
int minimax(int board[SIZE][SIZE], int depth, int alpha, int beta, bool isMaximizingPlayer, int player) {
    int MAX_DEPTH = 5;
    if (hasPlayerWon(board, PLAYER))
        return player == PLAYER ? 10 : -10;
    else if (hasPlayerWon(board, COMPUTER))
        return player == COMPUTER ? 10 : -10;
    else if (isBoardFull(board))
        return 0;
    else if (depth >= MAX_DEPTH)
        return 0;

    if (isMaximizingPlayer) {
        int maxScore = -1000; //INT_MIN;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = player;
                    int score = minimax(board, depth + 1, alpha, beta, false, player);
                    board[i][j] = EMPTY;
                    maxScore = std::max(maxScore, score);
                    alpha = std::max(alpha, maxScore);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return maxScore;
    } 
    
    else {
        int minScore = 1000; //INT_MAX;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = 3 - player;
                    int score = minimax(board, depth + 1, alpha, beta, true, player);
                    board[i][j] = EMPTY;
                    minScore = std::min(minScore, score);
                    beta = std::min(beta, minScore);
                    if (beta <= alpha)
                        break;
                }
            }
        }
        return minScore;
    }
}


void randCompMove(int board[SIZE][SIZE], int player){
    while(true){
        srand(time(0));
        int i = SIZE / 2; //rand() % SIZE + 0;
        int j = SIZE / 2; //rand() % SIZE + 0;
        if (board[i][j] == EMPTY){
            board[i][j] = player;
            break;
        }
        else{
            i += 1;
            j += 1;
            board[i][j] = player;
            break;
        }

    }
}

// Function to make the computer's move
void makeComputerMove(int board[SIZE][SIZE], int player) {
    int bestScore = -1000;
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    //int alpha = -1000;
    //int beta = 1000;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                board[i][j] = player;
                //std::cout << "LLL" << std::endl;
                int moveScore = minimax(board, 0, INT_MIN, INT_MAX, false, player);
                //std::cout << "LLL" << std::endl;
                board[i][j] = EMPTY;

                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMoveRow = i;
                    bestMoveCol = j;
                }
            }
        }
    }

    board[bestMoveRow][bestMoveCol] = player;
    std::cout << "Computer's move:" << std::endl;
    printBoard(board);
}

// Function to make the player's move
void makePlayerMove(int board[SIZE][SIZE]) {
    int row, col;

    do {
        std::cout << "Enter your move (row column): ";
        std::cin >> row >> col;
    } while (row < 0 || row >= SIZE || col < 0 || col >= SIZE || board[row][col] != EMPTY);
    
    board[row][col] = PLAYER;
}

// Function to play the game
void playGame() {
    int count = 0;
    int board[SIZE][SIZE] = {0};

    std::cout << "Tic-Tac-Toe" << std::endl;
    std::cout << "Player: X, Computer: O" << std::endl;
    std::cout << "Enter row and column numbers (0-" << SIZE - 1 << ")" << std::endl;
    std::cout << "-------------------" << std::endl;
    printBoard(board);
    std::cout << "-------------------" << std::endl;

    while (!isBoardFull(board) && !hasPlayerWon(board, PLAYER) && !hasPlayerWon(board, COMPUTER)) {
        makePlayerMove(board);

        if (isBoardFull(board) || hasPlayerWon(board, PLAYER) || hasPlayerWon(board, COMPUTER))
            break;

        if(count == 0 && SIZE > 3)
            randCompMove(board, COMPUTER);
            printBoard(board);
        ++count;

        if(count > 1 || SIZE < 4)
            makeComputerMove(board, COMPUTER);

        std::cout << "-------------------" << std::endl;
    }

    if (hasPlayerWon(board, PLAYER))
        std::cout << "Congratulations! You won." << std::endl;
    else if (hasPlayerWon(board, COMPUTER))
        std::cout << "Computer wins." << std::endl;
    else
        std::cout << "It's a draw." << std::endl;
}

int main() {
    playGame();
    return 0;
}# project3
