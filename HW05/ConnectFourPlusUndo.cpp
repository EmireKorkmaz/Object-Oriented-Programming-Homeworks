/*
    HW05 Emire Korkmaz
*/
#include "ConnectFourPlusUndo.h"

using namespace std;
namespace Korkmaz{

    ConnectFourPlusUndo::ConnectFourPlusUndo():ConnectFourPlus(){

    }
    void ConnectFourPlusUndo::undo(int index){
    	int a;
    	string move=moveArray[index];

        a = moveArray[index][0]-65; // gets move's integer value
        
        moveArray[index]="*"; // places "*" on the last move's place in moveArray.
        gameBoard[isColFilled[a]+1][a].setElement("*"); // places "*" on the last move's place.

        isColFilled[a]++; // increases empty cell number in a column
        full[a]++; // increases empty cell number in a column as well

    }
    // makes user's move after checking its validness
    int ConnectFourPlusUndo::play(string m){
        string command;
        int j;
        if(move=="V" || move=="U" || move == "Y"){
            cerr << "Invalid move. Try again.\n";
            return 2;
        }
        if(move.length()>2){
            command = move.substr(0,5);
            if(command=="UNDO"){
            	if(isFilled==0){
                	cerr << "Invalid move. Try again.\n";
                	return 2;
                }

            	isFilled--; // since a cell will be empty, decreases filled cell number
                undo(isFilled);
                return 3;
                
            }
            else if(command=="LOAD "){ // if move is load extract the filename and calls load function
                for (int i = command.length(), j=0; i < move.length(); ++i, ++j)
                   filename+=move[i];

                if(filename==compare){
                    cerr << "Error. You didn't specify any filename.\n";
                    exit(1);
                }
                load();

                return 2;
            }
            else if(command=="SAVE "){ // if move is save extract the filename and calls save function
                for (int i = command.length(), j=0; i < move.length(); ++i, ++j)
                    filename+=move[i];

                if(filename==compare){
                    cerr << "Error. You didn't specify any filename.\n";
                    exit(1);
                }
                if(save()==1){
                    return 1;
                }
            }
        
            else{
                cerr << "Invalid move. Try again.\n";
                return 2;
            }
        }
        if(isItFilled()){
            cerr << "Coloumn is full. Try again.\n";
            return 2;
        }

        if(!(validMove()) && command!="UNDO"){
            cerr << move << " is an invalid move. Try again.\n";
            return 2;
        }
        makeMove();
    }
}