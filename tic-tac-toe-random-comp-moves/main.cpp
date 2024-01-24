#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//functin to display board
void displayBoard(char board[3][3]){
    for (int i=0; i<3; ++i){
        cout<<"| ";
        for (int j=0; j<3; ++j){
            cout<<board[i][j]<<" | ";
        }
        cout<<endl<<"-------------"<<endl;
    }
}

//function to check whether player won or not?
bool checkWin(char board[3][3], char player){
    for (int i=0; i<3; ++i){
        
        //to check rows and columns
        if ((board[0][i] == player && board[1][i] == player && board[2][i] == player)||
        (board[i][0] == player && board[i][1] == player && board[i][2] == player)){
            return true;
        }
    }
    
    //to check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player)||
    (board[2][0] == player && board[1][1] == player && board[0][2] == player)){
        return true;
    }
    
    return false;
}

//function to check whether it is tie or not
bool checkTie(char board[3][3]){
    for (int i=0; i<3; ++i){
        for (int j=0; j<3; ++j){
            if (board[i][j] == ' '){                    //if there is empty space in the board, it's not a tie.
                return false;
            }
        }
    }
    return true;                                        //no empty space found, game is a tie.
}

void computerMove(char board[3][3]){
    int rows, cols;
    while(board[rows][cols] != ' '){              //generate random rows, cols values until empty space is found
        rows = rand()%3;
        cols = rand()%3;
    }
    
    board[rows][cols] = 'O';
}


int main()
{
    srand(time(0));
    
    char board[3][3] = {{' ', ' ', ' '},
                        {' ', ' ', ' '},
                        {' ', ' ', ' '}};
                        
    int rows, cols;
    
    while(true){
        cout<<"Enter coordinates:";
        cin>>rows>>cols;
        
        if(rows<0 || cols <0 || rows>=3 || cols>=3 || board[rows][cols] != ' '){
            cout<<"Invalid input. Try again!"<<endl;
            continue;
        }
        
        board[rows][cols] = 'X';
        displayBoard(board);
        cout<<endl<<endl;
        
        if (checkWin(board,'X')){
            displayBoard(board);
            cout<<"You win!";
            break;
        }
        
        if (checkTie(board)){
            displayBoard(board);
            cout<<"Game Tied!";
            break;
        }
        
        cout<<"Computer move:"<<endl;
        computerMove(board);
        displayBoard(board);
        cout<<endl<<endl;
        
        if (checkWin(board, 'O')){
            displayBoard(board);
            cout<<"Computer won!";
            break;
        }
        
        if (checkTie(board)){
            displayBoard(board);
            cout<<"Game Tied!";
            break;
        }
    }
    
    return 0;
}