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
