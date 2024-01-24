#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//function to display board
void displayboard(char board[3][3]){
    cout<<"-------------"<<endl;
    for (int i=0; i<3; ++i){
        cout<<"| ";
        for (int j=0; j<3; ++j){
            cout<<board[i][j]<<" | ";
        }
        cout<<endl<<"-------------"<<endl;
    }
}

//check if user won or not
bool checkWin(char board[3][3], char user){
    
    //check for rows and cols
    for (int i=0; i<3; ++i){
        if ((board[i][0]==user && board[i][1]==user && board[i][2]==user)||
            (board[0][i]==user && board[1][i]==user && board[2][i]==user)){
                return true;
        }
    }
    
    //check for diagonals
    if ((board[0][0]==user && board[1][1]==user && board[2][2]==user)||
        (board[2][0]==user && board[1][1]==user && board[0][2]==user)){
            return true;
    }
    
    return false;
}

//check if game tied or not
bool checkTie(char board[3][3]){
    for (int i=0; i<3; ++i){
        for (int j=0; j<3; ++j){
            if (board[i][j]==' '){
                return false;               //if there is empty space, match not tied yet
            }
        }
    }
    return true;
}

//minimax algorithm for computer's move
int minimax(char board[3][3], int depth, bool isMaxmizing){
    
    //evaluating for the current state of the board
    if (checkWin(board, 'O')) return 1;
    if (checkWin(board, 'X')) return -1;
    if (checkTie(board)) return 0;
    
    //maximizing player (computer)
    if (isMaxmizing){
        int bestScore = -1000;
        for (int i=0; i<3; ++i){
            for (int j=0; j<3; ++j){
                if (board[i][j] == ' '){
                    board[i][j] = 'O';
                    bestScore = max(bestScore, minimax(board, depth+1, !isMaxmizing));
                    board[i][j] = ' '; //undo move
                }
            }
            
        }
        return bestScore;
    }
    
    //Minimizing player (human)
    else{
        int bestScore = 1000;
        for (int i=0; i<3; ++i){
            for (int j=0; j<3; ++j){
                if (board[i][j] == ' '){
                    board[i][j] = 'X';
                    bestScore = min(bestScore, minimax(board, depth+1, !isMaxmizing));
                    board[i][j] = ' ';
                }
            }
        }
        return bestScore;
    }
}

//computer input function
void compInput(char board[3][3]){
    int bestMove = -1;
    int bestScore = -1000;
    
    for (int i=0; i<3; ++i){
        for (int j=0; j<3; ++j){
            if (board[i][j] == ' '){
                board[i][j] = 'O';
                int moveScore = minimax(board, 0, false);
                board[i][j] = ' ';      //undo moveScore
                
                if (moveScore >bestScore){
                    bestScore = moveScore;
                    bestMove = i*3 + j;
                }
            }
        }
    }
    
    int row = bestMove/3;
    int col = bestMove%3;
    
    board[row][col] = 'O';      //computer's move
}

int main()
{
    srand(time(0));
    char board[3][3] = {{' ',' ',' '},
                        {' ',' ',' '},
                        {' ',' ',' '}};
    int row, col;                    
    while(true){
        //display current board position
        displayboard(board);
        
        cout<<"\n\nEnter coordinates:";
        cin>>row>>col;
        
        //wrong input
        if (row<0 || col<0 || row>=3 || col>=3 || board[row][col]!=' '){
            cout<<"\nInvalid coordinates, try again!";
            continue;
        }
        
        board[row][col] = 'X';
        
        //check user win condition
        if (checkWin(board, 'X')){
            displayboard(board);
            cout<<"\nYou won!";
            break;
        }
        
        //check tie condition
        if (checkTie(board)){
            displayboard(board);
            cout<<"\nGame Tied!";
            break;
        }
        
        //computer input
        compInput(board);
        
        //check user loss condition
        if (checkWin(board, 'O')){
            displayboard(board);
            cout<<"\nYou Loss!";
            break;
        }
        
        //check tie condition
        if (checkTie(board)){
            displayboard(board);
            cout<<"\nGame Tied!";
            break;
        }
    }
    return 0;
}