#ifndef EXCEL_HPP
#define EXCEL_HPP
# include <iostream>
# include <vector>
#include <string>
# include <iomanip>
using namespace std;
#pragma once

class MiniExcel
{
public:
    class Cell 
    {
    public :
        string data ;
        Cell * up ;
        Cell * down ;
        Cell * left ;
        Cell * right ;
        Cell ( string d = " ");
    };
    Cell * root ;
    Cell * current ;
    int rows ;
    int cols ;

    MiniExcel();
    void moveUp ();
    void moveDown ();
    void moveLeft ();
    void moveRight ();
    void clearRow ();
    void clearColumn ();
    void deleteRow ();
    void deleteColumn ();
    void insertRowAbove ();
    void insertRowBelow ();
    void insertColumnToLeft ();
    void insertColumnToRight ();
    void editCurrentCell();
    void printSheet() ;
    int getRowIndex(Cell* target);
    int getColIndex(Cell* target);

    void setData(const string& value) ;
    string getData() const ;
    vector <char> copy (int startRow , int startCol , int endRow , int endCol ) ;
    void paste ( const vector <char >& data , int startRow , int startCol ) ;

    ~MiniExcel();

};

#endif