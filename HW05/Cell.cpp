/*
    HW05 Emire Korkmaz
*/

#include "Cell.h"

using namespace std;
// compares two objects to see if they're equal
bool Cell::operator ==(const Cell& other) const{
    return (element == other.element);
}

// compares this object's element and a string
// to see if they are equal
bool Cell::operator ==(string s) const{
    return (element == s);
}
// compares two objects to see if they're equal
bool Cell::operator !=(const Cell& other) const{
    return (element != other.element);
}
// compares this object's element and a string
// to see if they are equal
bool Cell::operator !=(string s) const{
    return (element != s);
}
// turns[4]={"*", "X", "O", "O"}
// there is a string array called turns which has 4 values; "*", "X", "O", "O" (for computer)

// pre
Cell& Cell::operator++(){  // ++ operator changes the cell state from empty to user1, from user1 to user2,
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
Cell Cell::operator++(int ignore){    // ++ operator changes the cell state from empty to user1, from user1 to user2,
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
Cell& Cell::operator--(){ // -- operator changes the cell state from empty to computer, from user1 to empty,
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
Cell Cell::operator--(int ignore){ // -- operator changes the cell state from empty to computer, from user1 to empty,
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
ostream& operator<<( ostream& os, const Cell & obj){
    os << obj.element;
    return os;
}
istream& operator>>( istream& is, Cell & obj){
    is >> obj.element;
    return is;
}
string Cell::getElement() const{
    return element;
}
void Cell::setElement(string e){
    element=e;
}
void Cell::setRow(int r){
    row=r;
}

void Cell::setCol(string c){
    col=c;
}