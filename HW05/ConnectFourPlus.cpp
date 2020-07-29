/*
    HW05 Emire Korkmaz
*/
#include "ConnectFourPlus.h"

using namespace std;
namespace Korkmaz{
    // checks the whole board to see if there is any winner
    // this function checks the board to end the game, returns true if there is any winner
    bool ConnectFourPlus::whoWon(){
        string newPlace = (turn=="X" ? "x" : "o");
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j)  // checks horizontal
                if(j+3<colSize && gameBoard[i][j]!="*" && gameBoard[i][j]!=" " &&
                	gameBoard[i][j+1]!="*" && gameBoard[i][j+2]!="*" && gameBoard[i][j+3]!="*"){
                    if (gameBoard[i][j]==gameBoard[i][j+1] &&
                        gameBoard[i][j]==gameBoard[i][j+2] &&
                        gameBoard[i][j]==gameBoard[i][j+3]){ 
                        cout << endl << turn << " won.\n";
                        
                        gameBoard[i][j].setElement(newPlace);
                        gameBoard[i][j+1].setElement(newPlace);
                        gameBoard[i][j+2].setElement(newPlace);
                        gameBoard[i][j+3].setElement(newPlace);
                        return true;
                    }
                }
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j) // checks vertical
                if(i+3<rowSize && gameBoard[i][j]!="*" && gameBoard[i][j]!=" " && 
                	gameBoard[i+1][j]!="*" && gameBoard[i+2][j]!="*" && gameBoard[i+3][j]!="*")
                   
                    if (gameBoard[i][j]==gameBoard[i+1][j] &&
                        gameBoard[i][j]==gameBoard[i+2][j] &&
                        gameBoard[i][j]==gameBoard[i+3][j]){ 
                        cout << endl << turn << " won.\n";

    					gameBoard[i][j].setElement(newPlace);
                        gameBoard[i+1][j].setElement(newPlace);
                        gameBoard[i+2][j].setElement(newPlace);
                        gameBoard[i+3][j].setElement(newPlace);
    	                
                        return true;
                    }

        return false;
    }
}