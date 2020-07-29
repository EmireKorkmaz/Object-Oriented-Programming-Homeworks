/*
	HW05 Emire Korkmaz
	
	 There are three different types of ConnectFour games.
	One, only accepts horizontally or vertically connected cells.
	Another, only accepts diagonally connected cells. Another one 
	can undo the moves of the user or the computer until the
	beginning of the game. First, it takes type of game from user.
	It creates the game by checking user's choice. After that, calls
	object's playGame function to start the game.

*/
#include <iostream>
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"
#include <string>

using namespace std;
using namespace Korkmaz;
int main(int argc, char const *argv[])
{
	string c; // takes user's choice to create the game
	cout << "What is your choice to play?\n";
	cin >> c;
	
	if(c=="D"){ // ConnectFourDiag
		ConnectFourDiag obj;
		obj.playGame();
	}
	else if (c=="P"){ // ConnectFourPlus
		ConnectFourPlus obj;
		obj.playGame();
	}
	else if (c=="U"){ // ConnectFourPlusUndo
		ConnectFourPlusUndo obj;
		obj.playGame();
	}
	else
		cerr << "You entered a wrong choice.\n";

	return 0;
}