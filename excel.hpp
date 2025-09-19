#ifndef EXCEL_HPP
#define EXCEL_HPP
# include <iostream>
# include <vector>
# include <iomanip>
using namespace std;
#pragma once

class MiniExcel
{

private :
    class Cell 
    {
    public :
        char data ;
        Cell * up ;
        Cell * down ;
        Cell * left ;
        Cell * right ;
        Cell ( char d = '.') : data ( d ) , up ( nullptr ) , down ( nullptr ) ,
                left ( nullptr ) , right ( nullptr ) {}

    };
    Cell * root ;
    Cell * current ;
    int rows ;
    int cols ;
public:
    MiniExcel();
    void insertRowAbove ();
    void insertRowBelow ();
    void insertColumnToRight ();
    void insertColumnToLeft ();
    void deleteColumn ();
    void deleteRow ();
    void clearColumn ();
    void clearRow ();
    void moveUp ();
    void moveDown ();
    void moveLeft ();
    void moveRight ();

    void printSheet ()
    {
    Cell * rowPtr = root ;
    while ( rowPtr != nullptr )
    {
    Cell * colPtr = rowPtr ;
    while ( colPtr != nullptr )
    {
    // cout << setw (3) << colPtr - > data << " | ";
    // colPtr = colPtr - > right ;
    }
    cout << endl ;
    Cell * temp = rowPtr ;
    while ( temp != nullptr )
    {
    cout << " ----";
    // temp = temp - > right ;
    }
    cout << endl ;
    // rowPtr = rowPtr - > down ;
    }
    }   
    vector <char> copy (int startRow , int startCol , int endRow , int endCol ) ;
    void paste ( const vector <char >& data , int startRow , int startCol ) ;

    ~MiniExcel();

};

#endif