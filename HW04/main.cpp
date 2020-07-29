/*

    CSE 241 - HW04

    Emire Korkmaz
    
    This is a C++ program that plays the game of Connect Four.
    The game of Connect Four is played by two players
    (computer-user or user1-user2) on a two dimensional board (2D vector) with
    rectangular cells. Each cell is either computer, user, or empty. On the
    board '*' represents the empty cells, X represents the user1 cells and O
    represents the user2 (or Computer) cells. When program starts, it asks the
    user to choose the type of the game, it can be S or M. 'S' stands for single
    object and 'M' stands for multiple objects. For mode 'M', number of objects
    can be adjusted by changing the macro NUM_OF_GAMES, for default it will be 5.
    After choosing mode, it asks user to choose to play either against computer
    or against another opponent. And after all these, program asks a file name
    to determine size of the board. The game continues until all the board
    is filled or one of the players wins. For mode 'M', even if one of objects's game ends
    it keeps playing until all the objects are finished. This program also accepts commands for
    loading and saving the game board. For example, instead of giving the column letters,
    if the user enters the command LOAD FILE.TXT, program loads the game board from this file.
    Similarly, if the user enters the command SAVE FILE.TXT, program saves the current
    game status to this file. It also prints number of living cells on console in every move.
    There is a compare function to compare first and second object to see which one has the
    advantage to win the game. To be more accurate it begins to compare after at least 5 cells
    filled in each object.
    
*/


#include <iostream>
#include "ConnectFour.h"

using namespace std;

#define NUM_OF_OBJECTS 5
int ConnectFour::livingObj=0;

int main(){


    string gameMode, file, choice;
    int exit=0, whoIsDone[NUM_OF_OBJECTS], c=0, i=0, num; /* every object starts with 1, if they're ended then their value will be 0.
                                                        whoIsDone is an array to hold every object's value. It is used to prevent
                                                        the user to access an object that is done before. */
    for (int i = 0; i < NUM_OF_OBJECTS; ++i) {
        whoIsDone[i]=1;
    }

    cout << "Choose the game mode S/M: ";
    cin >> gameMode;

    if (gameMode=="M") {
        
        ConnectFour objects[NUM_OF_OBJECTS];

        while(i<NUM_OF_OBJECTS){
            objects[i].setMode("M");
            objects[i].playGame();
            i++;
        }

        /* i created a variable called exit whenever an object's done than exit will be increased.
            whenever exit hits NUM_OF_OBJECT, game would be over*/
        while (exit<NUM_OF_OBJECTS) { // if a game ends then it increases exit's value
            cout << "Which object do you want to play with?: ";
            cin >> num;
            if (cin.fail()) {
                cerr << "Invalid object." << endl;
                return -1;
            }
            if(whoIsDone[num-1]==0){
                cout << "This object cannot be used. "
                    << "Its game has ended. Choose another object.\n";
                continue;
            }
            if(num > NUM_OF_OBJECTS || num < 0){
                cerr << "Invalid object. Enter an object number between 0-"
                     << NUM_OF_OBJECTS << endl;
                continue;
            }
            objects[num - 1].printAll();
            objects[num - 1].setMode("M");
            if(objects[num - 1].playGame()) {
                whoIsDone[num-1]=0;
                exit += 1;
            }
            if (objects[0].getIsFilled()>4 && objects[1].getIsFilled()>4)
                if(objects[0]==objects[1])
                    cout << "First object is more likely to win the game.\n";
                else if(objects[0]!=objects[1])
                    cout << "Second object is more likely to win the game.\n";
        }
        cout << "Game is over.\n";
    }
    else if(gameMode=="S"){
        ConnectFour obj;
        obj.setMode("S");
        obj.playGame();
    }
    else{
        cerr << "invalid game mode.\n";
        return -1;
    }

    return 0;
}