/*
	HW05 Emire Korkmaz

	 This class is an abstract base class. It has required functions
	and their definitions. It has a "has a" relation between Cell class.
	By default, it plays Connect Four game as always. Asks user for size of
	board and choice. After creating the board, it asks for move from user and
	when it's computer's turn, takes computer's move. Checks the board after
	every move to see if there is a winner or not. It also can save the current
	game or load a previous saved game.
*/

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

#include <iostream>
#include <fstream>
#include "Cell.h"

using namespace std;
namespace Korkmaz{
class ConnectFourAbstract{
	public:
		virtual bool playGame();  // plays the game by asking each opponents in order
	protected:
		ConnectFourAbstract(string file);
		ConnectFourAbstract();
		ConnectFourAbstract(const ConnectFourAbstract& other);
		~ConnectFourAbstract();

		virtual void play(); // when user chooses to play against computer, decides the computer's move
	    virtual int play(string m); // for user's move
	    virtual void load(); // loads a saved game from given file
	    virtual int save(); // saves the current game to a given file
	    virtual inline int getRowSize()  const {  return rowSize;   } // the current height
	    virtual inline int getColSize()  const {  return colSize;   } // the current width
	    virtual void printAll(); // prints board
	    virtual bool whoWon(); // checks the whole board to see if there is any winner and returns true


	    virtual bool operator ==(const ConnectFourAbstract& other)const; // overloaded == operator compares two objects
	                                                // to see which object has the advantage to win the game
	    virtual bool operator !=(const ConnectFourAbstract& other)const; // overloaded != operator compares two objects
	    virtual inline int getIsFilled() const {  return isFilled;  } // returns number of cells filled for this object
	    virtual inline void setMode(string m){  mode=m; } // sets the game mode
		virtual void openFile(); // opens given file and reads the board into gameBoard
	    virtual bool isItFilled() const; // checks all columns to see if they are full or not
	    virtual bool validMove() const; // checks if a move is valid or not
	    virtual void makeMove(); // after being sure about a move's validance, this function makes the move
	    virtual ConnectFourAbstract& operator=(const ConnectFourAbstract& other); // overloaded assignment operator
	    virtual void inputs(); // takes inputs from user (row, col and choice)
	    virtual void beginning(); // initializes gameCells, isColFilled and full which is used to check if a coloumn is full or not
	    virtual inline void setChoice(string c){  choice = c; }
	    virtual inline void setFile(string f){ filename=f; } // sets the filename

	    Cell** gameBoard;
	    string * moveArray;
	    string letters[26]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N",
	                    "O","P","Q","R","S","T", "U", "V", "W", "X", "Y", "Z"};
	    int rowSize, colSize, isFilled=0, block=1, blank=0;
	    string turn="X", choice, filename, compare="\0", move, mode;
	    int* isColFilled, *full;
	    bool isFileOpened=false, deleteIt=false, enter;
};
}
#endif
