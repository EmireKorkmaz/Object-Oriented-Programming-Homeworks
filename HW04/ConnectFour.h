/*

    CSE 241 - HW04

    Emire Korkmaz

    ConnectFour.h
*/

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <iostream>

using namespace std;

class ConnectFour{
public:

    static int livingObj; // number of cells filled

    ConnectFour(string file);
    ConnectFour();
    ConnectFour(int r, int c);
    ~ConnectFour(); // destructor
    ConnectFour(const ConnectFour& other); // copy constructor

    bool playGame();  // plays the game by asking each opponents in order
    void printAll(); // prints board
    bool operator ==(const ConnectFour& other)const; // overloaded == operator compares two objects
                                                // to see which object has the advantage to win the game
    bool operator !=(const ConnectFour& other)const; // overloaded != operator compares two objects
                                                // to see which object has the advantage to win the game

    inline int getRowSize()  const {  return rowSize;   } // the current height
    inline int getColSize()  const {  return colSize;   } // the current width
    inline int getIsFilled() const {  return isFilled;  } // returns number of cells filled for this object

    inline void setMode(string m){  mode=m; } // sets the game mode
    
private:
    class Cell{
    public:
        Cell(int r, string c, string e):row(r), col(c), element(e){

        }
        Cell(){

        }
        // compares two objects to see if they're equal
        bool operator ==(const Cell& other) const{
            return (element == other.element);
        }

        // compares this object's element and a string
        // to see if they are equal
        bool operator ==(string s) const{
            return (element == s);
        }
        // compares two objects to see if they're equal
        bool operator !=(const Cell& other) const{
            return (element != other.element);
        }
        // compares this object's element and a string
        // to see if they are equal
        bool operator !=(string s) const{
            return (element != s);
        }
        // turns[4]={"*", "X", "O", "O"}
        // there is a string array called turns which has 4 values; "*", "X", "O", "O" (for computer)

        // pre
        Cell& operator++(){  // ++ operator changes the cell state from empty to user1, from user1 to user2,
                            // from user2 to computer, from computer back to empty.
            if(element==turns[0])
                element = turns[1];
            else if(element == turns[1])
                element = turns[2];

            else if(element==turns[2])
                element=  turns[3];

            else if(element==turns[3])
                element=  turns[0];
            return *this;
        }
        // post
        Cell operator++(int ignore){    // ++ operator changes the cell state from empty to user1, from user1 to user2,
                            // from user2 to computer, from computer back to empty.
            Cell temp;
            if(element==turns[0]){
                element = turns[1];
                temp.element = turns[1];
            }
            else if(element==turns[1]){
                element = turns[2];
                temp.element = turns[2];
            }
            else if(element==turns[2]){
                element = turns[3];
                temp.element = turns[3];
            }
            else if(element==turns[3]){
                element = turns[0];
                temp.element = turns[0];
            }
            return temp;
        }
        // pre
        Cell& operator--(){ // -- operator changes the cell state from empty to computer, from user1 to empty,
                            // from user2 to user1, from computer to user2.
            if(element==turns[0])
                element = turns[3];
            else if(element == turns[1])
                element = turns[0];

            else if(element==turns[2])
                element=  turns[1];

            else if(element==turns[3])
                element=  turns[2];
            return *this;
        }
        // post
        Cell operator--(int ignore){ // -- operator changes the cell state from empty to computer, from user1 to empty,
                            // from user2 to user1, from computer to user2.
            Cell temp;
            if(element==turns[0]){
                element = turns[3];
                temp.element = turns[3];
            }
            else if(element==turns[1]){
                element = turns[0];
                temp.element = turns[0];
            }
            else if(element==turns[2]){
                element = turns[1];
                temp.element = turns[1];
            }
            else if(element==turns[3]){
                element = turns[2];
                temp.element = turns[2];
            }
            return temp;
        }
        friend ostream& operator<<( ostream& os, const Cell & obj){
            os << obj.element;
            return os;
        }
        friend istream& operator>>( istream& is, Cell & obj){
            is >> obj.element;
            return is;
        }
        string getElement() const{
            return element;
        }
        void setElement(string e){
            element=e;
        }
        void setRow(int r){
            row=r;
        }
        void setCol(string c){
            col=c;
        }
        friend class ConnectFour;
    private:
        string turns[4]={"*", "X", "O", "O"};
        string element, col;
        int row;
    };


    void openFile(); // opens given file and reads the board into gameBoard
    void play(); // when user chooses to play against computer, decides the computer's move
    int play(string m); // for user's move
    void load(); // loads a saved game from given file
    int save(); // saves the current game to a given file
    bool isItFilled() const; // checks all columns to see if they are full or not
    bool validMove() const; // checks if a move is valid or not
    void makeMove(); // after being sure about a move's validance, this function makes the move
    bool whoWon(); // checks the whole board to see if there is any winner and returns true
    ConnectFour& operator=(const ConnectFour& other); // overloaded assignment operator
    void inputs(); // takes inputs from user (row, col and choice)
    void beginning(); // initializes gameCells, isColFilled and full which is used to check if a coloumn is full or not
    inline void setChoice(string c){  choice = c; }
    inline void setFile(string f){ filename=f; } // sets the filename

    Cell** gameBoard;
    string letters[26]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N",
                    "O","P","Q","R","S","T", "U", "V", "W", "X", "Y", "Z"};
    int rowSize, colSize, isFilled=0, block=1, blank=0;
    string turn="X", choice, filename, compare="\0", move, mode;
    int* isColFilled, *full;
    bool isFileOpened=false, deleteIt=false, enter;

};

#endif