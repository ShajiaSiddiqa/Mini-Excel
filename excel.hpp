#ifndef EXCEL_HPP
#define EXCEL_HPP
# include <iostream>
# include <vector>
# include <iomanip>
using namespace std;
#pragma once

class MiniExcel
{
public:
    class Cell 
    {
    public :
        char data ;
        Cell * up ;
        Cell * down ;
        Cell * left ;
        Cell * right ;
        Cell ( char d = ' ');
    };
    Cell * root ;
    Cell * current ;
    int rows ;
    int cols ;

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

    void printSheet() 
    {
        // Print column headers (A, B, C, ...)
        cout << "    "; // space for row labels
        for (int c = 0; c < cols; c++) {
            cout << "   " << char('A' + c) << "   ";
        }
        cout << "\n";

        for (int r = 0; r < rows; r++) {
            // ┌───┬───┐ top border of row
            for (int c = 0; c < cols; c++) 
            {
                if (c == 0) cout << (r == 0 ? "   ┌" : "   ├");
                for (int i = 0; i < 6; i++) cout << "─";
                cout << (c == cols - 1 ? (r == 0 ? "┐" : "┤") : (r == 0 ? "┬" : "┼"));
            }
            cout << "\n";

            // Row label (1, 2, 3...)
            cout << setw(2) << r + 1 << " ";

            // Cell content
            Cell* rowPtr = root;
            for (int i = 0; i < r; i++) rowPtr = rowPtr->down;

            Cell* colPtr = rowPtr;
            for (int c = 0; c < cols; c++) 
            {
                cout << "│  " << colPtr->data << "   ";
                colPtr = colPtr->right;
                if (c == cols - 1) cout << "│";
            }
            cout << "\n";
        }

        // └───┴───┘ bottom border
        for (int c = 0; c < cols; c++) 
        {
            if (c == 0) cout << "   └";
            for (int i = 0; i < 6; i++) cout << "─";
            cout << (c == cols - 1 ? "┘" : "┴");
        }
        cout << "\n";
    }

    vector <char> copy (int startRow , int startCol , int endRow , int endCol ) ;
    void paste ( const vector <char >& data , int startRow , int startCol ) ;

    ~MiniExcel();

};

#endif