/*

	CSE 241 - HW03

	Emire Korkmaz

	ConnectFour.h
*/

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ConnectFour {

public:
	static int livingObj; // number of cells filled
	static int temp;

    ConnectFour(); // invokes inputs function to get necessary inputs from user
    ConnectFour(int ro, int co, string ch); // initializes choice to ch and rowSize to ro and colSize to co
    ConnectFour(int ro, int co);
    inline int getRowSize() const   {  return rowSize;   } // the current height
    inline int getColSize() const   {  return colSize;   } // the current width
    inline int getLivingObj() const {  return livingObj; } // returns living object
    inline int getIsFilled() const  {  return isFilled;  } // returns number of cells filled for this object

    inline void setMode(string m){	mode=m; } // sets the game mode

    void play(); // when user chooses to play against computer, decides the computer's move
    int play(string); // for user's move
    void beginning(); // initializes gameCells and isColFilled which is used to check if a coloumn is full or not
    void printAll()const; // prints board
    bool playGame();  // plays the game by asking each opponents in order
    bool isItFilled() const; // checks all columns to see if they are full or not
    bool validMove() const; // checks if a move is valid or not
    void makeMove(); // after being sure about a move's validance, this function makes the move
    void load(); // loads a saved game from given file
    int save(); // saves the current game to a given file
    bool whoWon(); // checks the whole board to see if there is any winner, if game is ended returns 1, otherwise return false
    void inputs(); // takes inputs from user (row, col and choice)
    bool compareObj(const ConnectFour& other) const; // compares two objects to see which one has the advantage to win the game


private:
	// has 3 private members and their getters and setters
    class Cell{

    public:
		Cell(){
			row=0;
			col="A";
			element=".";
		}
        Cell(int r, string c, string x): row(r), col(c), element(x){

        }
        void setCol(string c){
            col=c;
        }
        void setRow(int r){
            row=r;
        }

        void setElement(string e){
            element=e;
        }

        string getElement() const{
            return element;
        }

        string getCol() const{
            return col;
        }
        int getRow() const{
            return row;
        }

    private:
        int row;
        string col, element; // ".", "x", "o"

    };

    vector< vector<Cell> > gameCells;
    string choice, move, turn="X", compare="\0",filename="", mode;
    bool endGame=false;
    int isFilled=0, colSize, block=1, blank=0, rowSize;
    vector<int> isColFilled;
    string letters[26]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N",
    				"O","P","Q","R","S","T", "U", "V", "W", "X", "Y", "Z"};
};


#endif
