/*
    HW05 Emire Korkmaz

    This class holds the position of the cell (A, B, C, etc)
    and the row number (1, 2, 3, etc). This class also includes
    all necessary setters/getters, constructors.
*/
#ifndef CELL_H
#define CELL_H

#include <iostream>
#include <string>

using namespace std;
class Cell{
    public:
        Cell(int r, string c, string e):row(r), col(c), element(e){

        }
        Cell(){

        }
        // compares two objects to see if they're equal
        bool operator ==(const Cell& other) const;

        // compares this object's element and a string
        // to see if they are equal
        bool operator ==(string s) const;
        // compares two objects to see if they're equal
        bool operator !=(const Cell& other) const;
        // compares this object's element and a string
        // to see if they are equal
        bool operator !=(string s) const;
        Cell& operator++();
        Cell operator++(int ignore);
        Cell& operator--();
        Cell operator--(int ignore);
        friend ostream& operator<<( ostream& os, const Cell & obj);
        friend istream& operator>>( istream& is, Cell & obj);

        string getElement() const;
        void setElement(string e);
        void setRow(int r);
        void setCol(string c);
    private:
        string turns[4]={"*", "X", "O", "O"};
        string element, col;
        int row;
    };

#endif