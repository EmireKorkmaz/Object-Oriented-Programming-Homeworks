/*
	CSE 241 - HW01

	Emire Korkmaz

	This is a C++ program that plays the game of Connect Four.
	The Connect Four game is played by two players
	(computer-user or user1-user2) on a two dimensional board (2D array) with
	rectangular cells. Each cell is either computer, user, or empty. On the
	board '.' represents the empty cells, X represents the user1 cells and O
	represents the user2 (or Computer) cells. When program starts, it asks the
	user to choose the type of the game, it can be PvP or PvC. After choosing
	type, program asks an integer number to determine size of the board. The
	game continues until all the board is filled or one of the players wins.

*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

bool isItFilled(int arr[], char move, int size);
void beginning(char table[][20], int isColFilled[], int size);
void printAll(char letters[], char table[][20], int size);
bool validMove(char move, char letters[], int size);
char computersMove(char table[][20], char letters[], int size, char turn);
void makeMove(char table[][20], int isColFilled[], char turn, char move);
bool whoWon(char table[][20], int size, char turn);
int inputSize();
char inputChoice();

int main(int argc, char const *argv[]){

	char choice, table[20][20], letters[20]={'A','B','C','D','E','F','G','H','I',
	'J','K','L','M','N','O','P','Q','R','S','T'};
	char turn='X', move;
	int size, isColFilled[20], isFilled=0, block=1; // isColFilled checks the current column if it's empty or full

	choice = inputChoice();

	size = inputSize();

	if (size==-1)
		return -1;

	beginning(table, isColFilled, size);
	printAll(letters, table, size);

	while(isFilled!=size*size){
		
		if(choice=='P'){
			cout << "Make your move.\n";
			if(!(cin >> move)){
				cout << move << " is an invalid move. Try again.\n";
				continue;
			}
		}
		else if(choice=='C' && block==1){
			cout << "Make your move.\n";
			if(!(cin >> move)){
				cout << move << " is an invalid move. Try again.\n";
				continue;
			}
			block=0;
		}
		else if(choice=='C' && block==0){
			move=computersMove(table, letters, size, turn);
			block=1;
		}

		if(isItFilled(isColFilled, move, size)){
			if(block==0)
				cout << "Coloumn is full. Try again.\n";
			if(block==1)
				block=0;
			else
				block=1;
			continue;
		}

		makeMove(table, isColFilled, turn, move);

		if(!(validMove(move, letters, size))){
			if(block==0)
				cout << move << " is an invalid move. Try again.\n";
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

		if(turn == 'O')
			turn = 'X';
		else
			turn = 'O';

		isFilled++;
	}
	cout << "The board is full\n";
	return 0;
}

// fills table with '.'s
void beginning(char table[][20], int isColFilled[], int size){
	for (int i = 0; i < size; ++i)
	{
		isColFilled[i]=size-1;
	}

	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			table[i][j]='.';
		}
	}
}

// prints board
void printAll(char letters[], char table[][20], int size){

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
bool validMove(char move, char letters[], int size){
	for (int i = 0; i < size; ++i)
		if(letters[i]==move)
			return true;

	return false;
}

// when the user chooses to play against computer, decides the computer's move
char computersMove(char table[][20], char letters[], int size, char turn){
	char move;
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){

			for (int j = 0; j < size; ++j){

                if(j<size-3 && table[i][j]!=turn){
                    if(table[i][j]==table[i][j+1] && table[i][j]==table[i][j+3] && table[i][j+2]=='.')
                        move = letters[j+2];
                    if(table[i][j]==table[i][j+2] && table[i][j]==table[i][j+3] && table[i][j+1]=='.')
                        move = letters[j+1];
                    if(table[i][j]==table[i-2][j+2] && table[i][j]==table[i-3][j+3] && table[i-1][j+1]=='.')
                        move = letters[j+1];
                }

                else if( table[i][j]!='.' && table[i][j]!=turn ){
                    if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j+3]=='.')
                        move=letters[j+3];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i][j]==table[i-3][j] && table[i-3][j]=='.')
                        move=letters[j];
                    else if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j+2]=='.')
                        move=letters[j+2];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i-3][j]=='.')
                        move=letters[j];
                }

                else if (table[i][j]!='.' && table[i][j]!=turn && j<size-3 && i<size-3){
                    if (table[i][j]==table[i+1][j+1] && table[i][j]==table[i+2][j+2] && table[i+3][j+3]=='.')
                        move = letters[j+3];
                    else if (table[i][j]==table[i-1][j-1] && table[i][j]==table[i-2][j-2] && table[i-3][j-3]=='.')
                        move = letters[j-3];
                    else if (table[i][j]==table[i+1][j+1] && table[i+2][j+2] =='.')
                        move = letters[j+2];
                    else if(table[i][j]==table[i-1][j-1] && table[i-2][j-2]=='.')
                        move = letters[j-2];
                }

                else if( table[i][j]!='.' && table[i][j]==turn ){
                    if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j+3]=='.')
                        move=letters[j+3];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i][j]==table[i-3][j] && table[i-3][j]=='.')
                        move=letters[j];
                    else if (j<size-3 && table[i][j]==table[i][j+1] && table[i][j+2]=='.')
                        move=letters[j+2];
                    else if(i<size-3 && table[i][j]==table[i-1][j] && table[i-3][j]=='.')
                        move=letters[j];
                }

                else if (table[i][j]!='.' && table[i][j]==turn && j<size-3 && i<size-3){
                    if (table[i][j]==table[i+1][j+1] && table[i][j]==table[i+2][j+2] && table[i+3][j+3]=='.')
                        move = letters[j+3];
                    else if (table[i][j]==table[i-1][j-1] && table[i][j]==table[i-2][j-2] && table[i-3][j-3]=='.')
                        move = letters[j-3];
                    else if (table[i][j]==table[i+1][j+1] && table[i+2][j+2] =='.')
                        move = letters[j+2];
                    else if(table[i][j]==table[i-1][j-1] && table[i-2][j-2]=='.')
                        move = letters[j-2];
                }
                else{
                	move=letters[rand() % 4 ];
                }
            }
		}
	}
	if(move=='\0')
		for (int i = 0; i < size; ++i)
			if (table[i][rand() % 4 ] == '.')
				move=letters[rand() % 4 ];
	return move;	
}

// checks all columns to see if they are full or not
bool isItFilled(int arr[], char move, int size){
	int m;

	switch(move){
		case 'A': m=0;
				break;
		case 'B': m=1;
				break;
		case 'C': m=2;
				break;
		case 'D': m=3;
				break;
		case 'E': m=4;
				break;
		case 'F': m=5;
				break;
		case 'G': m=6;
				break;
		case 'H': m=7;
				break;
		case 'I': m=8;
				break;
		case 'J': m=9;
				break;
		case 'K': m=10;
				break;
		case 'L': m=11;
				break;
		case 'M': m=12;
				break;
		case 'N': m=13;
				break;
		case 'O': m=14;
				break;
		case 'P': m=15;
				break;
		case 'Q': m=16;
				break;
		case 'R': m=17;
				break;
		case 'S': m=18;
				break;
		case 'T': m=19;
				break;
	}

	for (int i = 0; i < size; ++i)
		if (arr[i]<0 && m==i){
			return true;
		}

	return false;
}

// after being sure about a move's validance, this function makes the move
void makeMove(char table[][20], int isColFilled[], char turn, char move){
	switch(move){
		case 'A': table[isColFilled[0]][0]=turn;
				  isColFilled[0]--;
				break;
		case 'B': table[isColFilled[1]][1]=turn;
				  isColFilled[1]--;
				break;
		case 'C': table[isColFilled[2]][2]=turn;
				  isColFilled[2]--;
				break;
		case 'D': table[isColFilled[3]][3]=turn;
				  isColFilled[3]--;
				break;
		case 'E': table[isColFilled[4]][4]=turn;
				  isColFilled[4]--;
				break;
		case 'F': table[isColFilled[5]][5]=turn;
				  isColFilled[5]--;
				break;
		case 'G': table[isColFilled[6]][6]=turn;
				  isColFilled[6]--;
				break;
		case 'H': table[isColFilled[7]][7]=turn;
				  isColFilled[7]--;
				break;
		case 'I': table[isColFilled[8]][8]=turn;
				  isColFilled[8]--;
				break;
		case 'J': table[isColFilled[9]][9]=turn;
				  isColFilled[9]--;
				break;
		case 'K': table[isColFilled[10]][10]=turn;
				  isColFilled[10]--;
				break;
		case 'L': table[isColFilled[11]][11]=turn;
				  isColFilled[11]--;
				break;
		case 'M': table[isColFilled[12]][12]=turn;
				  isColFilled[12]--;
				break;
		case 'N': table[isColFilled[13]][13]=turn;
				  isColFilled[13]--;
				break;
		case 'O': table[isColFilled[14]][14]=turn;
				  isColFilled[14]--;
				break;
		case 'P': table[isColFilled[15]][15]=turn;
				  isColFilled[15]--;
				break;
		case 'Q': table[isColFilled[16]][16]=turn;
				  isColFilled[16]--;
				break;
		case 'R': table[isColFilled[17]][17]=turn;
				  isColFilled[17]--;
				break;
		case 'S': table[isColFilled[18]][18]=turn;
				  isColFilled[18]--;
				break;
		case 'T': table[isColFilled[19]][19]=turn;
				  isColFilled[19]--;
				break;
	}
}

// checks the whole board to see if there is any winner
bool whoWon(char table[][20], int size, char turn){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if(j<size-3 && table[i][j]!='.'){
				if (table[i][j]==table[i][j+1] && table[i][j]==table[i][j+2] && table[i][j]==table[i][j+3]){	
					cout << endl << turn << " won.\n";
					table[i][j]=turn+32;
					table[i][j+1]=turn+32;
					table[i][j+2]=turn+32;
					table[i][j+3]=turn+32;
					return true;
				}
			}
		}
	}

	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if(j<size-3 && table[j][i]!='.'){
				if (table[j][i]==table[j+1][i] && table[j][i]==table[j+2][i] && table[j][i]==table[j+3][i]){	
					cout << endl << turn << "  won.\n";
					table[j][i]=turn+32;
					table[j+1][i]=turn+32;
					table[j+2][i]=turn+32;
					table[j+3][i]=turn+32;
					return true;
				}
			}
		}
	}
	
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			if(table[i][j]!='.'){
				if (table[i][j]==table[i+1][j+1] && table[i][j]==table[i+2][j+2] && table[i][j]==table[i+3][j+3]){	
					cout << endl << turn << " won.\n";
					table[i][j]=turn+32;
					table[i+1][j+1]=turn+32;
					table[i+2][j+2]=turn+32;
					table[i+3][j+3]=turn+32;
					return true;
				}
				else if (table[i][j]==table[i+1][j-1] && table[i][j]==table[i+2][j-2] && table[i][j]==table[i+3][j-3]){	
					table[i][j]=turn+32;
					table[i+1][j-1]=turn+32;
					table[i+2][j-2]=turn+32;
					table[i+3][j-3]=turn+32;
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
		cout << "Invalid input for size.\n";
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
		cout << "Invalid choice. Try again.\n";
		cin >> choice;
	}
	return choice;
}
