/*

	CSE 241 - HW03

	Emire Korkmaz

	ConnectFour.cpp
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include "ConnectFour.h"

ConnectFour::ConnectFour(){
    inputs();
    beginning();
    printAll();
}
ConnectFour::ConnectFour(int ro, int co, string ch): rowSize(ro), colSize(co), choice(ch){
    beginning();
    printAll();
}
ConnectFour::ConnectFour(int ro, int co): rowSize(ro), colSize(co), choice("C"){
	beginning();
    printAll();
}
// initializes gameCells and isColFilled which is used to check if a coloum is full or not
void ConnectFour::beginning(){
  
    for (int i = 0; i < colSize; ++i)
    {
        isColFilled.push_back(rowSize-1);
    }

    for (int i = 0; i < rowSize; ++i){
        vector<Cell> temp;
        for (int j = 0; j < colSize; ++j){
            temp.push_back(Cell(j, letters[i],"."));
        }
        gameCells.push_back(temp);
    }
}

// prints board
void ConnectFour::printAll() const{

    cout << endl;

    for (int i = 0; i < colSize; ++i){
        cout << letters[i];
    }

    cout << endl;

    for (int i = 0; i < gameCells.size(); ++i){

        for (int j = 0; j < gameCells[i].size() && j<colSize; ++j){
            cout << gameCells.at(i).at(j).getElement();
        }
        cout << endl;
    }
}
// plays the game by asking each opponents in order
// returns true if the is ended for any reason, returns false if game is not finished yet
bool ConnectFour::playGame(){
    string m;
    int objTurn=0, retVal; // the current object's turn ends until the next time, when objTurn is 2

    while(true){

        if(choice=="P" || (choice=="C" && block==1)){
            if (blank==0){
                int order = (turn=="X" ? 1 : 2);
                cout << "P" << order << ": ";
            }

            getline(cin, move);

            if (move==compare){
                blank=1;
                continue;
            }

            blank=0;

            m=move;

            retVal = play(m);

            if(retVal==2)
    			continue;
    		else if (retVal==1)
    			return true;

            block=0;
        }
        else if(choice=="C" && block==0){
            play();
            if(isItFilled()){
                cerr << "Coloumn is full. Try again.\n";
                continue;
            }

            if(!(validMove())){
                cerr << move << " is an invalid move. Try again.\n";
                continue;
            }
            makeMove();
            block=1;
        }

        printAll();
        if(whoWon()){
            printAll();
            return true;
        }

        if(turn == "O")
            turn = "X";
        else
            turn = "O";

        isFilled++;
        objTurn++;
        livingObj++;

        if (isFilled==colSize*rowSize){
            cout << "Board is full.\n";
            return true;
        }
        cout << "Living cells : " << livingObj << endl;
        if (mode=="M" && objTurn==2)
        	break;
    }
    return false;
}

// checks all columns to see if they are full or not
bool ConnectFour::isItFilled() const{
    int m;
    string temp=move;
    m = int(temp.front())-65;
    for (int i = 0; i < colSize; ++i)
        if (isColFilled[i]<0 && m==i){
            return true;
        }
    return false;
}

// checks if a move is valid or not
bool ConnectFour::validMove() const{
    for (int i = 0; i < colSize; ++i)
        if(letters[i]==move)
            return true;
    return false;
}

// after being sure about a move's validance, this function makes the move
void ConnectFour::makeMove(){
    int a;

    a = move[0]-65;
    gameCells.at(isColFilled[a]).at(a).setElement(turn);
    isColFilled[a]--;
}
// checks the whole board to see if there is any winner
// this function checks the board to end the game, returns true if there is any winner
bool ConnectFour::whoWon(){
    string newPlace = (turn=="X" ? "x" : "o");
    for (int i = 0; i < rowSize; ++i){
        for (int j = 0; j < colSize; ++j){
            if(j+3<colSize && gameCells[i][j].getElement()!="."){
                if (gameCells[i][j].getElement()==gameCells[i][j+1].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i][j+2].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i][j+3].getElement()){  
                    cout << endl << turn << " won.\n";
                    gameCells[i][j].setElement(newPlace);
                    gameCells[i][j+1].setElement(newPlace);
                    gameCells[i][j+2].setElement(newPlace);
                    gameCells[i][j+3].setElement(newPlace);
                    return true;
                }
            }
        }
    }
    for (int i = 0; i < rowSize; ++i){
        for (int j = 0; j < colSize; ++j){
            if(i+3<rowSize && gameCells[i][j].getElement()!="."){
                if (gameCells[i][j].getElement()==gameCells[i+1][j].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i+2][j].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i+3][j].getElement()){  
                    cout << endl << turn << " won.\n";
                    gameCells[i][j].setElement(newPlace);
                    gameCells[i+1][j].setElement(newPlace);
                    gameCells[i+2][j].setElement(newPlace);
                    gameCells[i+3][j].setElement(newPlace);
                    return true;
                }
            }
        }
    }
    for (int i = 0; i < rowSize; ++i){
        for (int j = 0; j < colSize; ++j){
            if (j+3<colSize && i+3<rowSize && gameCells[i][j].getElement()!="." &&
            	gameCells[i][j].getElement()==gameCells[i+1][j+1].getElement() &&
                gameCells[i][j].getElement()==gameCells[i+2][j+2].getElement() &&
                gameCells[i][j].getElement()==gameCells[i+3][j+3].getElement()){  
                cout << endl << turn << " won.\n";
                gameCells[i][j].setElement(newPlace);
                gameCells[i+1][j+1].setElement(newPlace);
                gameCells[i+2][j+2].setElement(newPlace);
                gameCells[i+3][j+3].setElement(newPlace);
                return true;
            }
            if (i+3<rowSize && gameCells[i][j].getElement()!="." && j>2 &&
            		gameCells[i][j].getElement()==gameCells[i+1][j-1].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i+2][j-2].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i+3][j-3].getElement()){  
                gameCells[i][j].setElement(newPlace);
                gameCells[i+1][j-1].setElement(newPlace);
                gameCells[i+2][j-2].setElement(newPlace);
                gameCells[i+3][j-3].setElement(newPlace);
                cout << endl << turn << " won.\n";
                return true;
            }
            if (j+3<colSize && gameCells[i][j].getElement()!="." && i>2 &&
            		gameCells[i][j].getElement()==gameCells[i-1][j+1].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i-2][j+2].getElement() &&
                    gameCells[i][j].getElement()==gameCells[i-3][j+3].getElement()){  
                gameCells[i][j].setElement(newPlace);
                gameCells[i-1][j+1].setElement(newPlace);
                gameCells[i-2][j+2].setElement(newPlace);
                gameCells[i-3][j+3].setElement(newPlace);
                cout << endl << turn << " won.\n";
                return true;
            }
            
        }
    }
    return false;
}

// when the user chooses to play against computer, decides the computer's move
void ConnectFour::play(){
    srand(time(NULL));
    for (int i = 0; i < rowSize; ++i){
        for (int j = 0; j < colSize; ++j) {
            if( gameCells[i][j].getElement()!=turn){
                if(j<colSize-3 && gameCells[i][j+2].getElement()=="." &&
                	gameCells[i][j].getElement()==gameCells[i][j+1].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i][j+3].getElement())
                    move = letters[j+2];
                else if(j<colSize-3 && gameCells[i][j+1].getElement()=="." &&
                	gameCells[i][j].getElement()==gameCells[i][j+2].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i][j+3].getElement())
                    move = letters[j+1];
                else if( j<colSize-3 &&gameCells[i][j+3].getElement()=="." &&
                	gameCells[i][j].getElement()==gameCells[i][j+1].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i][j+2].getElement())
                    move = letters[j+3];
                else if(j>2 && gameCells[i][j-3].getElement()=="." &&
                	gameCells[i][j].getElement()==gameCells[i][j-1].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i][j-2].getElement())
                    move = letters[j-3];

                if (j<colSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i][j+1].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i][j+2].getElement() &&
                	gameCells[i][j+3].getElement()==".")
                    move=letters[j+3];
                else if(i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i-3][j].getElement() &&
                	gameCells[i-3][j].getElement()==".")
                    move=letters[j];
                else if (j<colSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i][j+1].getElement() &&
                	gameCells[i][j+2].getElement()==".")
                    move=letters[j+2];
                else if(i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j].getElement() &&
                	gameCells[i-3][j].getElement()==".")
                    move=letters[j];

                if (j<colSize-3 && i<rowSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i+1][j+1].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i+2][j+2].getElement() &&
                	gameCells[i+3][j+3].getElement()==".")
                    move = letters[j+3];
                else if (j>2 && i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j-1].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i-2][j-2].getElement() &&
                	gameCells[i-3][j-3].getElement()==".")
                    move = letters[j-3];
                else if (j<colSize-3 && i<rowSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i+1][j+1].getElement() &&
                	gameCells[i+2][j+2].getElement() ==".")
                    move = letters[j+2];
                else if(j>2 && i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j-1].getElement() &&
                	gameCells[i-2][j-2].getElement()==".")
                    move = letters[j-2];
            }

            else if( gameCells[i][j].getElement()!="." &&
            		gameCells[i][j].getElement()==turn ){
                if (j<colSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i][j+1].getElement() &&
                	gameCells[i][j].getElement()==gameCells[i][j+2].getElement() &&
                	gameCells[i][j+3].getElement()==".")
                    move=letters[j+3];
                else if(i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j].getElement() && 
                	gameCells[i][j].getElement()==gameCells[i-3][j].getElement() &&
                	gameCells[i-3][j].getElement()==".")
                    move=letters[j];
                else if (j<colSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i][j+1].getElement() && 
                	gameCells[i][j+2].getElement()==".")
                    move=letters[j+2];
                else if(i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j].getElement() && 
                	gameCells[i-3][j].getElement()==".")
                    move=letters[j];
 
                if (j<colSize-3 && i<rowSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i+1][j+1].getElement() && 
                	gameCells[i][j].getElement()==gameCells[i+2][j+2].getElement() && 
                	gameCells[i+3][j+3].getElement()==".")
                    move = letters[j+3];
                else if (j>2 && i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j-1].getElement() && 
                	gameCells[i][j].getElement()==gameCells[i-2][j-2].getElement() && 
                	gameCells[i-3][j-3].getElement()==".")
                    move = letters[j-3];
                else if (j<colSize-3 && i<rowSize-3 &&
                	gameCells[i][j].getElement()==gameCells[i+1][j+1].getElement() && 
                	gameCells[i+2][j+2].getElement() ==".")
                    move = letters[j+2];
                else if(j>2 && i>2 &&
                	gameCells[i][j].getElement()==gameCells[i-1][j-1].getElement() &&
                	gameCells[i-2][j-2].getElement()==".")
                    move = letters[j-2];
            }
            else{
                move=letters[rand() % 4 ];
            }
        }
    }
    if(move=="\0") {
        for (int i = 0; i < rowSize; ++i)
            if (gameCells[i][rand() % 4].getElement() == ".")
                move = letters[rand() % 4];
    }
}

// takes inputs from user (row, col and choice)
void ConnectFour::inputs(){

    cout << "Enter coloumn size: ";
    cin >> colSize;
    if (colSize<4 || colSize>26){
        cout << "Invalid coloumn size.\n";
        exit(1);
    }
    cout << "Enter row size: ";
    cin >> rowSize;
        if (rowSize<4){
        cout << "Invalid row size.\n";
        exit(1);
    }
    cout << "player | computer: ";
    cin >> choice;

    if(!(choice == "P" || choice == "C")){
        cerr << "Invalid choice.\n";
        exit(1);
    }
}
void ConnectFour::load(){

    string x, letter, col, c,l;
    ifstream bucky;
    int newR, newC;
    if (filename[filename.length()-1]<97){

        filename[filename.length()-1]+=' ';
        filename[filename.length()-2]+=' ';
        filename[filename.length()-3]+=' ';
    }

    if(!(filename[filename.length()-1]==116 &&
    	filename[filename.length()-2]==120 && 
    	filename[filename.length()-3]==116)){
        cerr << "Invalid file name. File must be a text file.\n";
        exit(1);
    }

    bucky.open(filename);

    if (bucky.fail()){
        cerr << "Error while opening file.\n";
        exit(1);
    }
    temp=isFilled;
    livingObj-=temp;
    bucky >> c >> rowSize >> colSize >> isFilled >> turn >> block >> letter >> col;
    temp=isFilled;
    livingObj+=temp;
    for (int i = 0; i < gameCells.size(); ++i){
        for (int j = 0; j < gameCells[i].size(); ++j)
            gameCells[i].pop_back();
    }
   
    if (c=="\0")
    {
        cerr << "Error! filename is empty.\n";
        exit(1);
    }
    choice=c;

    for (int i = 0; i < colSize; ++i)
    {
        isColFilled[i]=col[i]-48;
    }
    gameCells.resize(rowSize);

    for (int i = 0; i < gameCells.size(); ++i){
        bucky >> x;
        gameCells[i].assign(colSize, Cell());
        for (int j = 0; j < colSize; ++j){
            c=x[j];
            l=letter[j];
            gameCells[i][j]=Cell();
            gameCells[i][j].setElement(c);
            gameCells[i][j].setRow(i);
            gameCells[i][j].setCol(l);
           }

   }

    printAll();

    for (int i = 0; i < colSize; ++i){
        letters[i]=letter[i];
    }

    cout << "Size: " << rowSize << "x" << colSize << "  -  Choice: \"" 
         << choice << "\"\nIt's " << turn << "'s turn.\n";

    printAll();
}

int ConnectFour::save(){

    string x="", letter="";
    ofstream bucky;

    if (filename[filename.length()-1]<97){

        filename[filename.length()-1]+=' ';
        filename[filename.length()-2]+=' ';
        filename[filename.length()-3]+=' ';
    }

    if(!(filename[filename.length()-1]==116 &&
    	filename[filename.length()-2]==120 &&
    	filename[filename.length()-3]==116)){
        cerr << "Invalid file name. File must be a text file.\n";
        exit(1);
    }

    bucky.open(filename);

    if (bucky.fail()){
        cerr << "Error while opening file.\n";
        exit(1);
    }

    for (int i = 0; i < colSize; ++i){
        letter+=letters[i];
    }

    bucky << choice << endl << rowSize << endl << colSize <<
    		 endl << isFilled << endl << turn << endl << 
    		 block << endl << letter << endl;

    for (int i = 0; i < colSize; ++i)
    {
        bucky << isColFilled[i];
    }
    bucky << endl;
    for (int i = 0; i < rowSize; ++i){
        for (int j = 0; j < colSize; ++j){
            x+=gameCells.at(i).at(j).getElement();
        }
        bucky << x;
        x="";
        bucky << endl;
    }
    return 1;
}
// makes user's move after checking its validness
int ConnectFour::play(string m){
	string command;
	int j;
	if(move=="V" || move=="U" || move == "Y"){
        cerr << "Invalid move. Try again.\n";
        return 2;
    }
    if(move.length()>2){
        command = move.substr(0,5);
        if(command=="LOAD "){
            for (int i = command.length(), j=0; i < move.length(); ++i, ++j)
                filename+=move[i];

            if(filename==compare){
                cerr << "Error. You didn't specify any filename.\n";
                exit(1);
            }
            load();

            return 2;
        }
        else if(command=="SAVE "){
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

    if(!(validMove())){
        cerr << move << " is an invalid move. Try again.\n";
        return 2;
    }
    makeMove();
}
/* takes another object ConnectFour as parameter and
compares the Connect Four games. It returns true is the first game is better for the user, otherwise it
returns false. To be more accurate it begins to compare after at least 5 cells filled in each object.*/
bool ConnectFour::compareObj(const ConnectFour& other)const{
    int o1=0, o2=0;
    for (int i = 0; i < other.getRowSize(); ++i)
        for (int j = 0; j < other.getColSize(); ++j){
            if (j<colSize-3 && other.gameCells[i][j].getElement()!="." &&
            	other.gameCells[i][j].getElement()==other.gameCells[i][j+1].getElement() &&
                other.gameCells[i][j].getElement()==other.gameCells[i][j+2].getElement() &&
                other.gameCells[i][j+3].getElement()==".")
                o2++;
            if (j<colSize-3 && i<rowSize-3 && other.gameCells[i][j].getElement()!="." &&
            	other.gameCells[i][j].getElement()==other.gameCells[i+1][j+1].getElement() &&
                other.gameCells[i][j].getElement()==other.gameCells[i+2][j+2].getElement() &&
                other.gameCells[i+3][j+3].getElement()==".")
                o2++;
            if(i>2 && other.gameCells[i][j].getElement()!="." &&
            	other.gameCells[i][j].getElement()==other.gameCells[i-1][j].getElement() &&
                other.gameCells[i][j].getElement()==other.gameCells[i-3][j].getElement() &&
                other.gameCells[i-3][j].getElement()==".")
                o2++;

        }

    for (int i = 0; i < getRowSize(); ++i)
        for (int j = 0; j < getColSize(); ++j){
            if (j<colSize-3 && gameCells[i][j].getElement()!="." &&
            	gameCells[i][j].getElement()==gameCells[i][j+1].getElement() &&
                gameCells[i][j].getElement()==gameCells[i][j+2].getElement() &&
                gameCells[i][j+3].getElement()==".")
                o1++;
            if (j<colSize-3 && i<rowSize-3 && gameCells[i][j].getElement()!="." &&
            	gameCells[i][j].getElement()==gameCells[i+1][j+1].getElement() &&
                gameCells[i][j].getElement()==gameCells[i+2][j+2].getElement() &&
                gameCells[i+3][j+3].getElement()==".")
                o1++;
            if(i>2 && gameCells[i][j].getElement()!="." &&
            	gameCells[i][j].getElement()==gameCells[i-1][j].getElement() &&
                gameCells[i][j].getElement()==gameCells[i-3][j].getElement() &&
                gameCells[i-3][j].getElement()==".")
                o1++;

        }
        return (o1>o2 ? true : false);
}