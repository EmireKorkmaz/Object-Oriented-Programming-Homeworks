#include <fstream>
#include "ConnectFourAbstract.h"
using namespace std;
namespace Korkmaz{
    ConnectFourAbstract::ConnectFourAbstract(string file): filename(file){
        openFile();
        printAll();
    }
    ConnectFourAbstract::ConnectFourAbstract(){
        inputs();
        beginning();
    }
    // copy constructor
    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& other){
        rowSize=other.rowSize;
            colSize=other.colSize;
            for (int i = 0; i < rowSize; ++i)
                delete [] gameBoard[i];
            delete [] gameBoard;

            gameBoard = new Cell*[rowSize];
            for (int i = 0; i < rowSize; ++i)
                gameBoard[i] = new Cell[colSize];
    }

    ConnectFourAbstract::~ConnectFourAbstract(){
        for (int i = 0; i < rowSize; ++i)
            delete [] gameBoard[i];

        delete [] gameBoard;
        gameBoard=nullptr;

        delete [] full;
        full=nullptr;

        delete [] isColFilled;
        isColFilled=nullptr;
    }

    // prints board
    void ConnectFourAbstract::printAll(){
        cout << endl;
        for (int i = 0; i < colSize; ++i)
            cout << letters[i];		// first prints letters
        cout << endl;
        for (int i = 0; i < rowSize; ++i){
            for (int j = 0; j < colSize; ++j)
                cout << gameBoard[i][j];
            cout << endl;
        }
    }

    void ConnectFourAbstract::beginning(){
        gameBoard = new Cell*[rowSize];
        for (int i = 0; i < rowSize; ++i)
            gameBoard[i] = new Cell[colSize];

        
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j)
                gameBoard[i][j].setElement("*");  

        isColFilled= new int[colSize];  // creates isColFilled with the size of coloumn
        full= new int[colSize]; // creates full as well
        moveArray= new string[rowSize*colSize];

        for (int i = 0; i < colSize; ++i)
            moveArray[i]="*";
        for (int i = 0; i < colSize; ++i)
            isColFilled[i]=rowSize-1;

        for (int i = 0; i < colSize; ++i)   // fills every element of full with rowSize
            full[i]=rowSize-1;
      

        printAll();
    }

    // plays the game by asking each opponents in order
    // returns true if the is ended for any reason, returns false if game is not finished yet
    bool ConnectFourAbstract::playGame(){

        string m;
        int objTurn=0, retVal; // the current object's turn ends until the next time, when objTurn is 2
        while(isFilled!=colSize*rowSize){

            if(choice=="P" || (choice=="C" && block==1)){ // block variable is to block playGame to ask for
            										//computer input when turn is not computer's
                if (blank==0){
                    int order = (turn=="X" ? 1 : 2);
                    cout << "P" << order << ": ";
                }
                getline(cin, move);
                
                if (cin.eof()){ // exits whenever hits end of file
                    exit(1);
                }

                if (move==compare){ // getline takes null for the first input, i created a variable blank to make sure
                					//	when getline takes a null input it won't be executed
                    blank=1;
                    continue;
                }

                if (move.length()==0){ // exits whenever an input is empty
                    exit(1);
                }
                
                blank=0;

                m=move;
                retVal = play(m); 

                if(retVal==2)	// if retVal is 2 then loop continues, else it returns true
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
            if(move!="UNDO"){
                moveArray[isFilled]=move;
                 isFilled++;
            }
            
            if(whoWon()){
                printAll();
                return true;
            }

            if(turn == "O")
                turn = "X";
            else
                turn = "O";

           

        }
        cout << "Board is full.\n";
        return false;
    }
    // assignment operator
    ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract& other){
        if(rowSize!=other.rowSize && colSize!=other.colSize){
        							// deletes all dynamic array to add other's arrays after being sure about other is not ths object
            rowSize=other.rowSize;
            colSize=other.colSize;
            for (int i = 0; i < rowSize; ++i)
                delete [] gameBoard[i];
            delete [] gameBoard;

            gameBoard = new Cell*[rowSize];
            for (int i = 0; i < rowSize; ++i)
                gameBoard[i] = new Cell[colSize];

            delete [] isColFilled;
            isColFilled= new int[colSize];

            delete [] full;
            full= new int[colSize];
        }
        // after deleting dynamic arrays, writes other's arrays into this object's arrays
        for (int i = 0; i < rowSize; ++i)
        	for (int j = 0; j < colSize; ++j)
        		gameBoard[i][j]=other.gameBoard[i][j];

        for (int i = 0; i < colSize; ++i)
            isColFilled[i]=other.isColFilled[i];

        for (int i = 0; i < colSize; ++i)
            full[i]=other.full[i];

        return *this;
    }

    // opens given file and reads the board into gameBoard
    void ConnectFourAbstract::openFile(){
        ifstream file;
        file.open(filename);
        string s, v, x;
        int line=0, max=0, d=0;
        while(getline(file, v)){
            s+=v;
            if(max<v.length())	// reads all characters from the given file
                max=v.length();
            line++;
        }
        rowSize=line;
        colSize=max;

        isColFilled= new int[colSize];	// creates isColFilled with the size of coloumn

    	full= new int[colSize]; // creates full as well

        for (int i = 0; i < colSize; ++i)
            isColFilled[i]=rowSize-1;

        for (int i = 0; i < colSize; ++i)	// fills every element of full with rowSize
            full[i]=rowSize-1;

        gameBoard = new Cell*[rowSize]; // creates a brand new gameBoard that fit into given shape
        for (int i = 0; i < rowSize; ++i)
            gameBoard[i] = new Cell[colSize];
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j){
                x=s[d];
                gameBoard[i][j] = Cell(i, letters[j], x);
                d++;	// appends all the characters into gameBoard array by creating a new Cell object for each character
            }

        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j){
                if(gameBoard[i][j] == " ")
                	full[j]--; // decreases full's value if there is a white space in a coloumn
            }

        file.close();
        printAll();
    }

    // checks all columns to see if they are full or not
    bool ConnectFourAbstract::isItFilled() const{
        int m;
        string temp=move;
        m = int(temp.front())-65;
        for (int i = 0; i < colSize; ++i)
            if (full[i]<0 && m==i){  // checks the coloumn for the given location if it's empty
                return true;
            }
        return false;
    }

    // checks if a move is valid or not
    bool ConnectFourAbstract::validMove() const{
        for (int i = 0; i < colSize; ++i)
            if(letters[i]==move)	// checks if move is valid or not
                return true;
        return false;
    }

    // after being sure about a move's validance, this function makes the move
    void ConnectFourAbstract::makeMove(){
        int a;
        a = move[0]-65;
        if (gameBoard[isColFilled[a]][a]=="*")
        {
            gameBoard[isColFilled[a]][a].setElement(turn); // uses isColFilled to make a move.
            isColFilled[a]--;							// writes move into given location by using isColFilled which is used to
            											// write move bottom of the coloumn and decreases full array by 1 which is used
            											// to see if a coloumn is empty or not
            full[a]--;
        }
        else{
        	while(gameBoard[isColFilled[a]][a]==" "){
    	    	isColFilled[a]--;
    	    }
    	    gameBoard[isColFilled[a]][a].setElement(turn); 
    	    isColFilled[a]--;
    	    full[a]--;
        }
    }


    // when the user chooses to play against computer, decides the computer's move
    void ConnectFourAbstract::play(){
        srand(time(NULL));
        for (int i = 0; i < rowSize; ++i){
            for (int j = 0; j < colSize; ++j) {
                if( gameBoard[i][j]!=turn){ // decides computer's move by checking is there is a 'xx*x' situation
                    if(j<colSize-3 && gameBoard[i][j+2]=="*" &&
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j+1] &&
                        gameBoard[i][j]==gameBoard[i][j+3])
                        move = letters[j+2];
                    else if(j<colSize-3 && gameBoard[i][j+1]=="*" && // x*xx
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j+2] &&
                        gameBoard[i][j]==gameBoard[i][j+3])
                        move = letters[j+1];
                    else if( j<colSize-3 &&gameBoard[i][j+3]=="*" && // xxx*
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j+1] &&
                        gameBoard[i][j]==gameBoard[i][j+2])
                        move = letters[j+3];
                    else if(j>2 && gameBoard[i][j-3]=="*" && // vertically xxx*
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j-1] &&
                        gameBoard[i][j]==gameBoard[i][j-2])
                        move = letters[j-3];

                    if (j<colSize-3 && // vertically xxx*
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j+1] &&
                        gameBoard[i][j]==gameBoard[i][j+2] &&
                        gameBoard[i][j+3]=="*")
                        move=letters[j+3];
                    else if(i>2 && // *xxx
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i-1][j] &&
                        gameBoard[i][j]==gameBoard[i-3][j] &&
                        gameBoard[i-3][j]=="*")
                        move=letters[j];
                    else if (j<colSize-3 && // vertically xx*
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j+1] &&
                        gameBoard[i][j+2]=="*")
                        move=letters[j+2];
                    else if(i>2 &&
                        gameBoard[i][j]!=" " && // *x*x
                        gameBoard[i][j]==gameBoard[i-1][j] &&
                        gameBoard[i-3][j]=="*")
                        move=letters[j];

                    if (j<colSize-3 && i<rowSize-3 &&
                        gameBoard[i][j]!=" " && // diagonal xxx*
                        gameBoard[i][j]==gameBoard[i+1][j+1] &&
                        gameBoard[i][j]==gameBoard[i+2][j+2] &&
                        gameBoard[i+3][j+3]=="*")
                        move = letters[j+3];
                    else if (j>2 && i>2 && // diagonal xxx*
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i-1][j-1] &&
                        gameBoard[i][j]==gameBoard[i-2][j-2] && 
                        gameBoard[i-3][j-3]=="*")
                        move = letters[j-3];
                    else if (j<colSize-3 && i<rowSize-3 && // diagonal *xxx
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i+1][j+1] &&
                        gameBoard[i+2][j+2] =="*")
                        move = letters[j+2];
                    else if(j>2 && i>2 &&   //diagonal xx*x
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i-1][j-1] &&
                        gameBoard[i-2][j-2]=="*")
                        move = letters[j-2];
                }

                else if( gameBoard[i][j]!="*" &&
                    gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==turn ){ // xxx*
                    if (j<colSize-3 &&
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j+1] &&
                        gameBoard[i][j]==gameBoard[i][j+2] &&
                        gameBoard[i][j+3]=="*")
                        move=letters[j+3];
                    else if(i>2 &&
                        gameBoard[i][j]!=" " && // vertical xxx*
                        gameBoard[i][j]==gameBoard[i-1][j] &&
                        gameBoard[i][j]==gameBoard[i-3][j] &&
                        gameBoard[i-3][j]=="*")
                        move=letters[j];
                    else if (j<colSize-3 && // xx*x
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i][j+1] &&
                        gameBoard[i][j+2]=="*")
                        move=letters[j+2];
                    else if(i>2 &&
                        gameBoard[i][j]!=" " && // vertical *xxx
                        gameBoard[i][j]==gameBoard[i-1][j] &&
                        gameBoard[i-3][j]=="*")
                        move=letters[j];
     
                    if (j<colSize-3 && i<rowSize-3 && // diagonal xxx*
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i+1][j+1] &&
                        gameBoard[i][j]==gameBoard[i+2][j+2] &&
                        gameBoard[i+3][j+3]=="*")
                        move = letters[j+3];
                    else if (j>2 && i>2 && // diagonal *xxx
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i-1][j-1] &&
                        gameBoard[i][j]==gameBoard[i-2][j-2] &&
                        gameBoard[i-3][j-3]=="*")
                        move = letters[j-3];
                    else if (j<colSize-3 && i<rowSize-3 && // diagonal xx*x
                        gameBoard[i][j]!=" " &&
                        gameBoard[i][j]==gameBoard[i+1][j+1] &&
                        gameBoard[i+2][j+2] =="*")
                        move = letters[j+2];
                    else if(j>2 && i>2 &&
                        gameBoard[i][j]!=" " && // **xx
                        gameBoard[i][j]==gameBoard[i-1][j-1] &&
                        gameBoard[i-2][j-2]=="*")
                        move = letters[j-2];
                }
                else{
                    move=letters[rand() % 4 ];
                }
            }
        }
        if(move=="\0") { // if there is no suitable place to make a move, chooses randomly
            int x=rand() % 4;
            for (int i = 0; i < rowSize; ++i)
                if (gameBoard[i][x]!=" " && gameBoard[i][x] == "*")
                    move = letters[x];
        }
    }

    // checks the whole board to see if there is any winner
    // this function checks the board to end the game, returns true if there is any winner
    bool ConnectFourAbstract::whoWon(){
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

    // takes inputs from user (row, col and choice)
    void ConnectFourAbstract::inputs(){

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
    // makes user's move after checking its validness
    int ConnectFourAbstract::play(string m){
        string command;
        int j;
        if(move=="V" || move=="U" || move == "Y"){
            cerr << "Invalid move. Try again.\n";
            return 2;
        }

        filename="";
        if(move.length()>2){
            command = move.substr(0,5);
            if(command=="LOAD "){ // if move is load extract the filename and calls load function
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

        if(!(validMove())){
            cerr << move << " is an invalid move. Try again.\n";
            return 2;
        }
        makeMove();
    }
    /* takes another object ConnectFourAbstract as parameter and
    compares the Connect Four games. It returns true is the first game is better for the user, otherwise it
    returns false. To be more accurate it begins to compare after at least 5 cells filled in each object.*/
    bool ConnectFourAbstract::operator ==(const ConnectFourAbstract& other)const{
        int o1=0, o2=0; // checks the whole board to see if any of the components is close to win the game
        for (int i = 0; i < other.getRowSize(); ++i)
            for (int j = 0; j < other.getColSize(); ++j){
                if (j<colSize-3 && other.gameBoard[i][j]!="*" && //  xxx*
                	other.gameBoard[i][j]!=" " && other.gameBoard[i][j+1]!="*" &&
                	other.gameBoard[i][j+2]!="*" &&
                    other.gameBoard[i][j]==other.gameBoard[i][j+1] &&
                    other.gameBoard[i][j]==other.gameBoard[i][j+2] &&
                    other.gameBoard[i][j+3]=="*")
                    o2++;
                if (j<colSize-3 && i<rowSize-3 && other.gameBoard[i][j]!="*" && // diagonal xxx*
                	other.gameBoard[i][j]!=" " && other.gameBoard[i+1][j+1]!="*" &&
                	other.gameBoard[i+2][j+2]!="*" &&
                    other.gameBoard[i][j]==other.gameBoard[i+1][j+1] &&
                    other.gameBoard[i][j]==other.gameBoard[i+2][j+2] &&
                    other.gameBoard[i+3][j+3]=="*")
                    o2++;
                if(i>2 && other.gameBoard[i][j]!="*" && // vertical xxx*
                	other.gameBoard[i][j]!=" " && other.gameBoard[i-1][j]!="*" &&
                	other.gameBoard[i-2][j]!="*" &&
                    other.gameBoard[i][j]==other.gameBoard[i-1][j] &&
                    other.gameBoard[i][j]==other.gameBoard[i-3][j] &&
                    other.gameBoard[i-3][j]=="*")
                    o2++;

            }

        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j){
                if (j<colSize-3 && gameBoard[i][j]!="*" && //  xxx*
                	gameBoard[i][j]!=" " && gameBoard[i][j+1]!="*" &&
                	gameBoard[i][j+2]!="*" &&
                    gameBoard[i][j]==gameBoard[i][j+1] &&
                    gameBoard[i][j]==gameBoard[i][j+2] &&
                    gameBoard[i][j+3]=="*")
                    o1++;
                if (j<colSize-3 && i<rowSize-3 && gameBoard[i][j]!="*" && // diagonal xxx*
                	gameBoard[i][j]!=" " && gameBoard[i+1][j+1]!="*" &&
                	gameBoard[i+2][j+2]!="*" &&
                    gameBoard[i][j]==gameBoard[i+1][j+1] &&
                    gameBoard[i][j]==gameBoard[i+2][j+2] &&
                    gameBoard[i+3][j+3]=="*")
                    o1++;
                if(i>2 && gameBoard[i][j]!="*" &&
                	gameBoard[i][j]!=" " && gameBoard[i-1][j]!="*" && // vertical xxx*
                	gameBoard[i-2][j]!="*" &&
                    gameBoard[i][j]==gameBoard[i-1][j] &&
                    gameBoard[i][j]==gameBoard[i-3][j] &&
                    gameBoard[i-3][j]=="*")
                    o1++;

            }
            return (o1>o2 ? true : false);
    }
    /* takes another object ConnectFourAbstract as parameter and
    compares the Connect Four games. It returns false is the first game is better for the user, otherwise it
    returns true. To be more accurate it begins to compare after at least 5 cells filled in each object.*/
    bool ConnectFourAbstract::operator !=(const ConnectFourAbstract& other)const{
        int o1=0, o2=0;
        for (int i = 0; i < other.getRowSize(); ++i)
            for (int j = 0; j < other.getColSize(); ++j){
                if (j<colSize-3 && other.gameBoard[i][j]!="*" && //  xxx*
                    other.gameBoard[i][j]==other.gameBoard[i][j+1] &&
                    other.gameBoard[i][j]==other.gameBoard[i][j+2] &&
                    other.gameBoard[i][j+3]=="*")
                    o2++;
                if (j<colSize-3 && i<rowSize-3 && other.gameBoard[i][j]!="*" && // diagonal xxx*
                    other.gameBoard[i][j]==other.gameBoard[i+1][j+1] &&
                    other.gameBoard[i][j]==other.gameBoard[i+2][j+2] &&
                    other.gameBoard[i+3][j+3]=="*")
                    o2++;
                if(i>2 && other.gameBoard[i][j]!="*" && // vertical xxx*
                    other.gameBoard[i][j]==other.gameBoard[i-1][j] &&
                    other.gameBoard[i][j]==other.gameBoard[i-3][j] &&
                    other.gameBoard[i-3][j]=="*")
                    o2++;

            }

        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j){
                if (j<colSize-3 && gameBoard[i][j]!="*" && //  xxx*
                    gameBoard[i][j]==gameBoard[i][j+1] &&
                    gameBoard[i][j]==gameBoard[i][j+2] &&
                    gameBoard[i][j+3]=="*")
                    o1++;
                if (j<colSize-3 && i<rowSize-3 && gameBoard[i][j]!="*" && // diagonal xxx*
                    gameBoard[i][j]==gameBoard[i+1][j+1] &&
                    gameBoard[i][j]==gameBoard[i+2][j+2] &&
                    gameBoard[i+3][j+3]=="*")
                    o1++;
                if(i>2 && gameBoard[i][j]!="*" && // vertical xxx*
                    gameBoard[i][j]==gameBoard[i-1][j] &&
                    gameBoard[i][j]==gameBoard[i-3][j] &&
                    gameBoard[i-3][j]=="*")
                    o1++;

            }
            return (o1<o2 ? true : false);
    }

    // loads a saved game from given file
    void ConnectFourAbstract::load(){

        string x, letter, col, c,l, s, moves;
        ifstream bucky;
        int newR, newC, temp;
        if (filename[filename.length()-1]<97){ // checks file name's validness

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
        for (int i = 0; i < rowSize; ++i)
                delete [] gameBoard[i];
        delete [] gameBoard;

        temp=isFilled;
       // livingObj-=temp;	// subtracts old game's living cells

    	// reads all the necesarry variables from the file
        bucky >> c >> rowSize >> colSize >> isFilled >> turn >> block >> letter >> col >> moves;

        temp=isFilled; // adds new's games living cells
       // livingObj+=temp;
        if (c=="\0")
        {
            cerr << "Error! filename is empty.\n";
            exit(1);
        }
        choice=c;

        gameBoard = new Cell*[rowSize];
        for(int i=0; i<rowSize; ++i)
            gameBoard[i] = new Cell[colSize];

        for (int i = 0; i < colSize; ++i)
            isColFilled[i]=col[i]-48;

        for (int i = 0; i < colSize; ++i)
            full[i]=col[i]-48;

        int j=0;
        	while(getline(bucky, x)){
    	    	s+=x;
    	    }
    	int d=0;
        for (int i = 0; i < rowSize; ++i)
            for (int j = 0; j < colSize; ++j){ // write the game in the given file into gameBoard
                x=s[d];
                Cell temp;
                gameBoard[i][j] = temp;
                gameBoard[i][j].setElement(x);
                gameBoard[i][j].setRow(i);
                gameBoard[i][j].setCol(letters[j]);
                d++;
            }
        
        for (int i = 0; i < isFilled; ++i){
            moveArray[i] = moves[i];
        }
        cout << "Size: " << rowSize << "x" << colSize << "  -  Choice: \""
             << choice << "\"\nIt's " << turn << "'s turn.\n";
        bucky.close();
        printAll();

    }
    // saves the current game to a given file
    int ConnectFourAbstract::save(){

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
        // writes all the necesarry variables into the file
        bucky << choice << endl << rowSize << endl << colSize <<
                 endl << isFilled << endl << turn << endl <<
                 block << endl << letter << endl;

        for (int i = 0; i < colSize; ++i)
        {
            bucky << isColFilled[i];
        }
        bucky<< endl;

        for (int i = 0; i < isFilled; ++i)
        {
            bucky << moveArray[i];
        }
        for(int i=0; i<colSize; ++i)
        	full[i]=isColFilled[i];
        bucky << endl; // writes gameBoard into the given file
        for (int i = 0; i < rowSize; ++i){
            for (int j = 0; j < colSize; ++j){
                x+=gameBoard[i][j].getElement();
            }
            bucky << x;
            x="";
            bucky << endl;
        }
        
        bucky.close();
        return 1;
    }
}

