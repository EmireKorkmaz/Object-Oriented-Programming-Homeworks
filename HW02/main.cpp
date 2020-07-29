/*
	CSE 241 - HW02

	Emire_Korkmaz

	This is a C++ program that will play the game of Connect Four.
	The game of Connect Four is played by two players
	(computer-user or user1-user2) on a two dimensional board (2D array) with
	rectangular cells. Each cell is either computer, user, or empty. On the
	board '.' represents the empty cells, X represents the user1 cells and O
	represents the user2 (or Computer) cells. When program starts, it asks the
	user to choose the type of the game, it can be PvP or PvC. After choosing
	type, program asks an integer number to determine size of the board. The
	game continues until all the board is filled or one of the players wins.
	 This program also accepts commands for loading and saving the game board.
	For example, instead of giving the column letters, if the user enters the
	command LOAD FILE.TXT, program loads the game board from this file. Similarly,
	if the user enters the command SAVE FILE.TXT, program saves the current
	game status to this file.

*/

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
using namespace std;

bool isItFilled(int arr[], string move, int size);
void beginning(string table[][20], int isColFilled[], int size);
void printAll(const string letters[], const string table[][20], const int& size);
bool validMove(string move, string letters[], int size);
string computersMove(string table[][20], string letters[], int size, string turn);
void makeMove(string table[][20], int isColFilled[], string turn, string move);
bool whoWon(string table[][20], int size, string turn);
int inputSize();
char inputChoice();
void upper(string &str);
void load(string file, string table[][20], string& choice, string& turn, int& block, int& size, int& isFilled, string letters[], int isColFilled[]);
void save(string file, string table[][20], string& choice, string& turn, int& block, int& size, int& isFilled, string letters[], int isColFilled[]);

int main(int argc, char const *argv[]){

	string choice, table[20][20], letters[20]={"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T"};
	string turn="X", move, command, filename="";
	int isColFilled[20], isFilled=0, block=1, blank=0; // isColFilled checks the current column if it's empty or full

	decltype(2*2) size;
	auto compare="\0";

	choice = inputChoice();

	size = inputSize();

	if (size==-1)
		return -1;

	beginning(table, isColFilled, size);
	printAll(letters, table, size);

	while(isFilled!=size*size){
		
		if(choice=="P"){
			if (blank==0)
				cout << "Make your move.\n";

			getline(cin, move);
			
			if (move==compare){
				blank=1;
				continue;
			}

			blank=0;

			if(move=="V" || move=="U" || move == "Y"){
				cerr << "Invalid move. Try again.\n";
				continue;
			}


			if(move.length()>1){
				command = move.substr(0,5);
				if(command=="LOAD "){
					for (int i = command.length(), j=0; i < move.length(); ++i, ++j)
						filename+=move[i];

					if(filename==compare){
						cerr << "Error. You didn't specify any filename.\n";
						exit(1);
					}

					load(filename, table, choice, turn, block, size, isFilled, letters, isColFilled);

					continue;
				}
				else if(command=="SAVE "){
					for (int i = command.length(), j=0; i < move.length(); ++i, ++j)
						filename+=move[i];
					
					if(filename==compare){
						cerr << "Error. You didn't specify any filename.\n";
						exit(1);
					}

					save(filename, table, choice, turn, block, size, isFilled, letters, isColFilled);

					return 0;
				}
				else{
					cerr << "Invalid move. Try again.\n";
					continue;
				}
			}
		}
		else if(choice=="C" && block==1){
			
			if (blank==0)
				cout << "Make your move.\n";

			getline(cin, move); // getline takes '\0' at first, to prevent this i declared a variable called blank
								// if it's 0 then it'll ask user to make a move.

			if (move==compare){
				blank=1;
				continue;
			}
			blank=0;

			if(move=="V" || move=="U" || move == "Y"){
				cerr << "Invalid move. Try again.\n";
				continue;
			}

			if(move.length()>1){
				command = move.substr(0,5);
				if(command=="LOAD "){
					for (int i = command.length(), j=0; i < move.length(); ++i, ++j)
						filename+=move[i];

					if(filename==compare){
						cerr << "Error. You didn't specify any filename.\n";
						exit(1);
					}

					load(filename, table, choice, turn, block, size, isFilled, letters, isColFilled);
					continue;
				}
				else if(command=="SAVE "){
					for (int i = command.length(), j=0; i < move.length(); ++i, ++j)
						filename+=move[i];

					if(filename==compare){
						cerr << "Error. You didn't specify any filename.\n";
						exit(1);
					}

					save(filename, table, choice, turn, block, size, isFilled, letters, isColFilled);

					return 0;
				}
				else{
					cerr << "Invalid move. Try again.\n";
					continue;
				}
			}
			block=0;
		}
		else if(choice=="C" && block==0){
			move=computersMove(table, letters, size, turn);
			block=1;
		}

		if(isItFilled(isColFilled, move, size)){
			if(block==0)
				cerr << "Coloumn is full. Try again.\n";
			if(block==1)
				block=0;
			else
				block=1;
			continue;
		}

		makeMove(table, isColFilled, turn, move);

		if(!(validMove(move, letters, size))){
			if(block==0)
				cerr << move << " is an invalid move. Try again.\n";
			if(block==1)
				block=0;
			else
				block=1;
			continue;
		}

		printAll(letters, table, size);

		if(whoWon(table, size, turn)){
			printAll(letters, table, size);
			return 0;
		}

		if(turn == "O")
			turn = "X";
		else
			turn = "O";

		isFilled++;
	}
	cout << "The board is full\n";
	return 0;
}

// fills table with '.'s
void beginning(string table[][20], int isColFilled[], int size=20){
	for (int i = 0; i < size; ++i)
	{
		isColFilled[i]=size-1;
	}

	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			table[i][j]=".";
		}
	}
}

// prints board
void printAll(const string letters[], const string table[][20], const int& size){

	cout << endl;

	for (int i = 0; i < size; ++i){
		cout << letters[i];
	}

	cout << endl;

	for (int i = 0; i < size; ++i){
		
		for (int j = 0; j < size; ++j){
			cout << table[i][j];
		}
		cout << endl;
	}
}

// checks if a move is valid or not
bool validMove(string move, string letters[], int size){
	for (int i = 0; i < size; ++i)
		if(letters[i]==move)
			return true;

	return false;
}

// when the user chooses to play against computer, decides the computer's move
string computersMove(string table[][20], string letters[], int size, string turn){
	string move;
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){

			for (int j = 0; j < size; ++j){

                if(j<size-3 && table[i][j]!=turn){
                    if(table[i][j]==table[i][j+1] && table[i][j]==table[i][j+3] && table[i][j+2]==".")
                        move = letters[j+2];
                    if(table[i][j]==table[i][j+2] && table[i][j]==table[i][j+3] && table[i][j-1]==".")
                        move = letters[j+1];
                    if(table[i][j]==table[i-2][j+2] && table[i][j]==table[i-3][j+3] && table[i-1][j+1]==".")
                        move = letters[j+1];
                }

                else if( table[i][j]!="." && table[i][j]!=turn ){
                    if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j+3]==".")
                        move=letters[j+3];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i][j]==table[i-3][j] && table[i-3][j]==".")
                        move=letters[j];
                    else if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j+2]==".")
                        move=letters[j+2];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i-3][j]==".")
                        move=letters[j];
                }

                else if (table[i][j]!="." && table[i][j]!=turn && j<size-3 && i<size-3){
                    if (table[i][j]==table[i+1][j+1] && table[i][j]==table[i+2][j+2] && table[i+3][j+3]==".")
                        move = letters[j+3];
                    else if (table[i][j]==table[i-1][j-1] && table[i][j]==table[i-2][j-2] && table[i-3][j-3]==".")
                        move = letters[j-3];
                    else if (table[i][j]==table[i+1][j+1] && table[i+2][j+2] ==".")
                        move = letters[j+2];
                    else if(table[i][j]==table[i-1][j-1] && table[i-2][j-2]==".")
                        move = letters[j-2];
                }

                else if( table[i][j]!="." && table[i][j]==turn ){
                    if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j+3]==".")
                        move=letters[j+3];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i][j]==table[i-3][j] && table[i-3][j]==".")
                        move=letters[j];
                    else if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j+2]==".")
                        move=letters[j+2];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i-3][j]==".")
                        move=letters[j];
                }

                else if (table[i][j]!="." && table[i][j]==turn && j<size-3 && i<size-3){
                    if (table[i][j]==table[i+1][j+1] && table[i][j]==table[i+2][j+2] && table[i+3][j+3]==".")
                        move = letters[j+3];
                    else if (table[i][j]==table[i-1][j-1] && table[i][j]==table[i-2][j-2] && table[i-3][j-3]==".")
                        move = letters[j-3];
                    else if (table[i][j]==table[i+1][j+1] && table[i+2][j+2] ==".")
                        move = letters[j+2];
                    else if(table[i][j]==table[i-1][j-1] && table[i-2][j-2]==".")
                        move = letters[j-2];
                }
                else{
                	move=letters[rand() % 4 ];
                }
            }
		}
	}
	if(move=="\0")
		for (int i = 0; i < size; ++i)
			if (table[i][rand() % 4 ] == ".")
				move=letters[rand() % 4 ];
	return move;	
}

// checks all columns to see if they are full or not
bool isItFilled(int arr[], string move, int size){
	int m;

	for (int i=0;i<move.length();i++)
    {
        m = move[i]-65;
    }

	for (int i = 0; i < size; ++i)
		if (arr[i]<0 && m==i){
			return true;
		}

	return false;
}

// after being sure about a move's validance, this function makes the move
void makeMove(string table[][20], int isColFilled[], string turn, string move){
	int a;
	for (int i=0;i<move.length();i++)
    {
        a = move[i]-65;
        table[isColFilled[a]][a]=turn;
		isColFilled[a]--;
    }

}

// checks the whole board to see if there is any winner
bool whoWon(string table[][20], int size, string turn){
	int newPlace = turn[0]+32;

	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if(j<size-3 && table[i][j]!="."){
				if (table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j]==table[i][j+3]){	
					cout << endl << turn << " won.\n";
					table[i][j]=newPlace;
					table[i][j+1]=newPlace;
					table[i][j+2]=newPlace;
					table[i][j+3]=newPlace;
					return true;
				}
			}
		}
	}

	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if(j<size-3 && table[j][i]!="."){
				if (table[j][i]==table[j+1][i] && table[j][i]==table[j+2][i] && table[j][i]==table[j+3][i]){	
					cout << endl << turn << "  won.\n";
					table[j][i]=newPlace;
					table[j+1][i]=newPlace;
					table[j+2][i]=newPlace;
					table[j+3][i]=newPlace;
					return true;
				}
			}
		}
	}
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if(table[i][j]!="."){
				if (table[i][j]==table[i+1][j+1] && table[i][j]==table[i+2][j+2] && table[i][j]==table[i+3][j+3]){	
					cout << endl << turn << " won.\n";
					table[i][j]=newPlace;
					table[i+1][j+1]=newPlace;
					table[i+2][j+2]=newPlace;
					table[i+3][j+3]=newPlace;
					return true;
				}
				else if (table[i][j]==table[i+1][j-1] && table[i][j]==table[i+2][j-2] && table[i][j]==table[i+3][j-3]){	
					table[i][j]=newPlace;
					table[i+1][j-1]=newPlace;
					table[i+2][j-2]=newPlace;
					table[i+3][j-3]=newPlace;
					cout << endl << turn << " won.\n";
					return true;
				}
			}
		}
	}
	return false;	
}

// asks user to enter the size parameter and checks its validness
int inputSize(){
	int s;

	cout << "Enter an even integer (between 4 and 20) for board's size." << endl;
	cin >> s;

	if((s==4 || s==6 || s==8 || s==10 || s==12 || s==14 || s==16 || s==18 || s==20)){
		return s;
	}
	else{
		cerr << "Invalid input for size.\n";
		return -1;
	}
}

// asks user to enter the choice parameter and checks its validness
char inputChoice(){
	char choice;
	cout << "    Connect Four\n";
	cout << "Enter \"P\" for PvP\n";
	cout << "Enter \"C\" for PvC\n";
	cin >> choice;

	while(!(choice == 'P' || choice == 'C')){
		cerr << "Invalid choice. Try again.\n";
		cin >> choice;
	}
	return choice;
}
// loads the game that is wanted from user with its related informations.
void load(string file, string table[][20], string& choice, string& turn, int& block, int& size, int& isFilled, string letters[], int isColFilled[]){

	string x, letter, col, c;
	ifstream bucky;

	if (file[file.length()-1]<97){

		file[file.length()-1]+=' ';
		file[file.length()-2]+=' ';
		file[file.length()-3]+=' ';
	}

	if(!(file[file.length()-1]==116 && file[file.length()-2]==120 && file[file.length()-3]==116)){
		cerr << "Invalid file name. File must be a text file.\n";
		exit(1);
	}

	bucky.open(file);

	if (bucky.fail()){
		cerr << "Error while opening file.\n";
		exit(1);
	}


	bucky >> c >> size >> isFilled >> turn >> block >> letter >> col;

	if (c=="\0")
	{
		cerr << "Error! File is empty.\n";
		exit(1);
	}
	choice=c;
	for (int i = 0; i < size; ++i)
	{
		isColFilled[i]=col[i]-48;
	}
	for (int i = 0; i < size; ++i){
		bucky >> x;
		for (int j = 0; j < size; ++j){
			table[i][j]=x[j];
		}
	}

	for (int i = 0; i < size; ++i){
		letters[i]=letter[i];
	}

	cout << "Size: " << size << "  -  Choice: \""<< choice << "\"\nIt's " << turn << "'s turn.\n";

	printAll(letters, table, size);
}		
// saves the game that is wanted from user with its related informations.
// it saves current board, user's choice to play, game turn, board's size
// number of how many cells were filled, number of how many empty cells
// on the board, a flag variable to use when user choose to play against
// computer.
void save(string file, string table[][20], string& choice, string& turn, int& block, int& size, int& isFilled, string letters[], int isColFilled[]){

	string x="", letter="";
	ofstream bucky;

	if (file[file.length()-1]<97){

		file[file.length()-1]+=' ';
		file[file.length()-2]+=' ';
		file[file.length()-3]+=' ';
	}

	if(!(file[file.length()-1]==116 && file[file.length()-2]==120 && file[file.length()-3]==116)){
		cerr << "Invalid file name. File must be a text file.\n";
		exit(1);
	}

	bucky.open(file);

	if (bucky.fail()){
		cerr << "Error while opening file.\n";
		exit(1);
	}

	for (int i = 0; i < size; ++i){
		letter+=letters[i];
	}

	bucky << choice << endl << size << endl << isFilled << endl << turn << endl << block << endl << letter << endl;

	for (int i = 0; i < size; ++i)
	{
		bucky << isColFilled[i];
	}
	bucky << endl;
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			x+=table[i][j];
		}
		bucky << x;
		x="";
		bucky << endl;
	}
}
