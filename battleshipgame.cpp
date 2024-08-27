// #include <iostream>
// #include <ctime>
// #include <cstdlib>

// using namespace std;

// const int BOARD_SIZE = 10;
// const int SHIPS = 1;

// char playerBoard[BOARD_SIZE][BOARD_SIZE];
// char computerBoard[BOARD_SIZE][BOARD_SIZE];

// void initializeBoard(char board[][BOARD_SIZE]) {
//     for (int i = 0; i < BOARD_SIZE; i++) {
//         for (int j = 0; j < BOARD_SIZE; j++) {
//             board[i][j] = 247;
//         }
//     }
// }

// void printBoard(char board[][BOARD_SIZE]) {
//     for (int i = 0; i < BOARD_SIZE; i++) {
//         for (int j = 0; j < BOARD_SIZE; j++) {
//             cout << board[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

// void placeShips(char board[][BOARD_SIZE]) {
//     srand(time(0));
//     for (int i = 0; i < SHIPS; i++) {
//         int x = rand() % BOARD_SIZE;
//         int y = rand() % BOARD_SIZE;
//         board[x][y] = 'S';
//     }
// }

// bool isValidMove(int x, int y) {
//     return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE;
// }

// bool isHit(char board[][BOARD_SIZE], int x, int y) {
//     return board[x][y] == 'S';
// }

// int main() {
//     initializeBoard(playerBoard);
//     initializeBoard(computerBoard);
//     placeShips(computerBoard);

//     int playerHits = 0;
//     int computerHits = 0;

//     while (playerHits < SHIPS && computerHits < SHIPS) {
//         // Player's turn
//         cout << "Player's turn:" << endl;
//         cout << "Enter target coordinates (x y): ";
//         int y, x;
//         cin >> x >> y;

//         if (isValidMove(x, y)) {
//             if (isHit(computerBoard, x, y)) {
//                 cout << "You hit the computer's ship!" << endl;
//                 computerBoard[x][y] = 'X';
//                 playerHits++;
//             } else {
//                 cout << "You missed." << endl;
//                 computerBoard[x][y] = 'O';
//             }
//         } else {
//             cout << "Invalid move. Try again." << endl;
//         }

//         cout << "Computer's board:" << endl;
//         printBoard(computerBoard);

//         // Check if player won
//         if (playerHits == SHIPS) {
//             cout << "Congratulations! You sank all of the computer's ships." << endl;
//             break;
//         }

//         // Computer's turn
//         cout << "Computer's turn:" << endl;
//         int computerX = rand() % BOARD_SIZE;
//         int computerY = rand() % BOARD_SIZE;

//         if (isHit(playerBoard, computerX, computerY)) {
//             cout << "Computer hit your ship!" << endl;
//             playerBoard[computerX][computerY] = 'X';
//             computerHits++;
//         } else {
//             cout << "Computer missed." << endl;
//             playerBoard[computerX][computerY] = 'O';
//         }

//         cout << "Your board:" << endl;
//         printBoard(playerBoard);

//         // Check if computer won
//         if (computerHits == SHIPS) {
//             cout << "Game over! The computer sank all of your ships." << endl;
//             break;
//         }
//     }

//     return 0;
// }





















#include<iostream>
#include<ctime>
#include<cstdlib>

using namespace std;

const int board_size = 10;
const int ship = 5;
const int lengths[ship] = {2, 3, 3, 4, 5};

char playerboard[board_size][board_size];
char computerboard[board_size][board_size];

void initializeboard(char board[][board_size])
{
    for(int i = 0; i < board_size; i++)
    {
        for(int j = 0; j < board_size; j++)
        {
            board[i][j] = '-';
        }
    }
}

void printboard(char board[][board_size])
{
    cout <<"  ";
    for(int i = 0; i < board_size; i++)
    {
        cout << i<<" ";
    }
    cout << endl;
    for(int i = 0; i < board_size; i++)
    {
        cout << i << " ";
        for(int j = 0; j < board_size; j++)
        {
            cout <<board[i][j] <<" "; 
        }
        cout << endl;
    }
}

void placeship(char board[][board_size])
{
    srand(time(0));
    for(int i = 0; i < ship; i++)
    {
        int x = rand() % 10;
        int y = rand() % 10;
        board[x][y] ='S';
    }
}

bool isvalidmove(int x, int y)
{
    return x >= 0 && x < board_size && y >= 0 && y < board_size;  
}

bool ishit(char board[][board_size], int x , int y)
{
    return board[x][y] == 'S';
}


bool isvalidplace(char board[][board_size], int x , int y, int length, bool horizontal)
{
    if(horizontal)
    {
        return y + length <= board_size;
    }else{
        return x + length <= board_size;
    }
}

bool shipoveranother(char board[][board_size], int x , int y, int length, bool horizontal)
{
    if(horizontal)
    {
        for(int i = 0; i < length; i++)
        {
            if(board[x][y + i] != '-')
            {
                return true;
            }
        }
    }else{
        for(int i = 0; i < length; i++)
        {
            if(board[x + i][y] != '-')
            {
                return true;
            }
        }
    }
    return false;
}

void arrangeship(char board[][board_size])
{
    srand(time(0));
    for(int i = 0; i < ship; i++)
    {
        bool horizontal = rand() % 2;
        int length = lengths[i];
        int x, y;
        do{
            x = rand() % 10;
            y = rand() % 10;
        }while(!isvalidplace(board, x ,y, length,horizontal) || shipoveranother(board, x, y, length, horizontal));
        for(int i = 0; i < length; i++)
        {
            if(horizontal)
            {
                board[x][y + i] = 'S';
            }else{
                board[x + i][y] = 'S'; 
            }
        }
    }
}


int main()
{
    initializeboard(playerboard);
    initializeboard(computerboard);
    arrangeship(computerboard);
    // placeship(computerboard);

    int playerhit = 0;
    int computerhit = 0;
    int remainship = 5;

    while(playerhit < ship && computerhit < ship)
    {
        int x , y;
        cout <<" Player turn :"<<endl;
        cout <<" Enter cordinate to attack (x y): ";
        cin >> y >> x;
        if(isvalidmove(x,y))
        {
            if(ishit(computerboard, x, y))
            {
                cout <<"You hit the computer's ship."<<endl;
                computerboard[x][y] = 'X';
                playerhit++;
            }else{
                cout <<"You miss your target."<<endl;
                computerboard[x][y] = '0';
            }
        }else{
            cout <<"Your input is invalid. Please try again."<<endl;
        }
        cout <<" Computer's board."<<endl;
        printboard(computerboard);

        if(playerhit == ship)
        {
            cout <<"Congratulation you hit your target."<<endl;
            break;
        }

        cout <<"Computer turn:"<<endl;
        int computerX = rand() % 10;
        int computerY = rand() % 10;

        if(ishit(playerboard, computerX, computerY))
        {
            cout <<"Computer hit your ship."<<endl;
            playerboard[computerX][computerY] = 'X';
            computerhit++;
        }else{
            cout <<"Computer miss it's target.";
            playerboard[computerX][computerY] = '0';
        }
        cout <<"Player's board."<<endl;
        printboard(playerboard);

        if(computerhit == ship)
        {
            cout <<"GameOver"<<endl;
            break;
        }
    }
    return 0;
}





















// #include <iostream>
// // #include <vector>
// #include <ctime>
// #include <cstdlib>

// using namespace std;

// const int BOARD_SIZE = 10;
// const int NUM_SHIPS = 5;
// const int SHIP_LENGTHS[NUM_SHIPS] = {2, 3, 3, 4, 5};

// // Function prototypes
// void initializeBoard(char board[][BOARD_SIZE]);
// void printBoard(char board[][BOARD_SIZE]);
// void placeShips(char board[][BOARD_SIZE]);
// bool isValidLocation(char board[][BOARD_SIZE], int row, int col, int length, bool horizontal);
// bool checkOverlap(char board[][BOARD_SIZE], int row, int col, int length, bool horizontal);
// void takeGuess(char board[][BOARD_SIZE], int& remainingShips);

// int main() {
//     char board[BOARD_SIZE][BOARD_SIZE];
//     int remainingShips = NUM_SHIPS;

//     initializeBoard(board);
//     placeShips(board);

//     while (remainingShips > 0) {
//         printBoard(board);
//         takeGuess(board, remainingShips);
//     }

//     cout << "Congratulations! You sank all the battleships!" << endl;

//     return 0;
// }

// void initializeBoard(char board[][BOARD_SIZE]) {
//     for (int i = 0; i < BOARD_SIZE; ++i) {
//         for (int j = 0; j < BOARD_SIZE; ++j) {
//             board[i][j] = '-';
//         }
//     }
// }

// void printBoard(char board[][BOARD_SIZE]) {
//     cout << "  ";
//     for (int i = 0; i < BOARD_SIZE; ++i) {
//         cout << i << " ";
//     }
//     cout << endl;
//     for (int i = 0; i < BOARD_SIZE; ++i) {
//         cout << i << " ";
//         for (int j = 0; j < BOARD_SIZE; ++j) {
//             cout << board[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

// void placeShips(char board[][BOARD_SIZE]) {
//     srand(time(nullptr));
//     for (int ship = 0; ship < NUM_SHIPS; ++ship) {
//         bool horizontal = rand() % 2== 0 ;
//         int length = SHIP_LENGTHS[ship];
//         int row, col;
//         do {
//             row = rand() % BOARD_SIZE;
//             col = rand() % BOARD_SIZE;
//         } while (!isValidLocation(board, row, col, length, horizontal)|| checkOverlap(board, row, col, length, horizontal) );

//         for (int i = 0; i < length; ++i) {
//             if (horizontal) {
//                 board[row][col + i] = 'A';
//             } else {
//                 board[row + i][col] = 'C';
//             }
//         }
//     }
// }

// bool isValidLocation(char board[][BOARD_SIZE], int row, int col, int length, bool horizontal) {
//     if (horizontal) {
//         return col + length <= BOARD_SIZE;
//     } else {
//         return row + length <= BOARD_SIZE;
//     }
// }

// bool checkOverlap(char board[][BOARD_SIZE], int row, int col, int length, bool horizontal) {
//     if (horizontal) {
//         for (int i = 0; i < length; ++i) {
//             if (board[row][col + i] != '-') {
//                 return true;
//             }
//         }
//     } else {
//         for (int i = 0; i < length; ++i) {
//             if (board[row + i][col] != '-') {
//                 return true;
//             }
//         }
//     }
//     return false;
// }

// void takeGuess(char board[][BOARD_SIZE], int& remainingShips) {
//     int row, col;
//     cout << "Enter row and column to guess (0-9): ";
//     cin >> row >> col;

//     if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE) {
//         cout << "Invalid input. Please enter numbers between 0 and 9." << endl;
//         return;
//     }

//     if (board[row][col] == 'S') {
//         cout << "Hit!" << endl;
//         board[row][col] = 'X';
//         remainingShips--;
//     } else if (board[row][col] == '-' || board[row][col] == 'X') {
//         cout << "Miss!" << endl;
//         board[row][col] = 'O';
//     } else {
//         cout << "You've already guessed this position!" << endl;
//     }
// }






















