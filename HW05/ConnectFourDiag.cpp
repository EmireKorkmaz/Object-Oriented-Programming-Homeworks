#include "ConnectFourDiag.h"

using namespace std;
namespace Korkmaz{
    // checks the whole board to see if there is any winner
    // this function checks the board to end the game, returns true if there is any winner
    bool ConnectFourDiag::whoWon(){
        string newPlace = (turn=="X" ? "x" : "o");

        for (int i = 0; i < rowSize; ++i){
            for (int j = 0; j < colSize; ++j){ // checks diagonal
                if (j+3<colSize && i+3<rowSize && gameBoard[i][j]!="*"
                    && gameBoard[i+1][j+1]!="*" && gameBoard[i+2][j+2]!="*" &&
                    gameBoard[i+3][j+3]!="*" &&
                    gameBoard[i][j]!=" " &&
                    gameBoard[i][j]==gameBoard[i+1][j+1] &&
                    gameBoard[i][j]==gameBoard[i+2][j+2] &&
                    gameBoard[i][j]==gameBoard[i+3][j+3]){ 
                    cout << endl << turn << " won.\n";

                    gameBoard[i][j].setElement(newPlace);
                    gameBoard[i+1][j+1].setElement(newPlace);
                    gameBoard[i+2][j+2].setElement(newPlace);
                    gameBoard[i+3][j+3].setElement(newPlace);

                    return true;
                }
                if (i+3<rowSize && gameBoard[i][j]!="*" && j>2 // checks diagonal
                    && gameBoard[i+1][j-1]!="*" && gameBoard[i+2][j-2]!="*" &&
                    gameBoard[i+3][j-3]!="*" && gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i+1][j-1] &&
                        gameBoard[i][j]==gameBoard[i+2][j-2] &&
                        gameBoard[i][j]==gameBoard[i+3][j-3]){ 
    	               
    	                gameBoard[i][j].setElement(newPlace);
    	                gameBoard[i+1][j-1].setElement(newPlace);
    	                gameBoard[i+2][j-2].setElement(newPlace);
    	                gameBoard[i+3][j-3].setElement(newPlace);
    	         
                    cout << endl << turn << " won.\n";
                    return true;
                }
                if (j+3<colSize && gameBoard[i][j]!="*" && i>2 // checks diagonal
                    && gameBoard[i-1][j+1]!="*" && gameBoard[i-2][j+2]!="*" &&
                    gameBoard[i-3][j+3]!="*" && gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i-1][j+1] &&
                        gameBoard[i][j]==gameBoard[i-2][j+2] &&
                        gameBoard[i][j]==gameBoard[i-3][j+3]){ 

    	                gameBoard[i][j].setElement(newPlace);
    	                gameBoard[i-1][j+1].setElement(newPlace);
    	                gameBoard[i-2][j+2].setElement(newPlace);
    	                gameBoard[i-3][j+3].setElement(newPlace);
    	                cout << endl << turn << " won.\n";
    	            
                    return true;
                }
               
            }
        }
        return false;
    }
}