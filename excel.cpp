#include "excel.hpp"


MiniExcel::MiniExcel() {
    rows = 5;
    cols = 5;

    root = new Cell(' ');
    current = root;

    // ----------- first row
    Cell* rowStart = root;
    for (int c = 1; c < cols; c++) 
    {
        Cell* newCell = new Cell(' ');
        rowStart->right = newCell;
        newCell->left = rowStart;
        rowStart = newCell;
    }

    // ---------- remaining rows
    Cell* aboveRow = root;
    for (int r = 1; r < rows; r++) 
    {
        Cell* newRowStart = new Cell(' ');
        aboveRow->down = newRowStart;
        newRowStart->up = aboveRow;

        // --------- Filling rest of row
        Cell* leftCell = newRowStart;
        Cell* aboveCell = aboveRow->right;

        for (int c = 1; c < cols; c++) 
        {
            Cell* newCell = new Cell(' ');
            leftCell->right = newCell;
            newCell->left = leftCell;

            // ----- linking vertically
            newCell->up = aboveCell;
            aboveCell->down = newCell;

            // ------ moving pointers right
            leftCell = newCell;
            aboveCell = aboveCell->right;
        }
        aboveRow = aboveRow->down;
    }
}

MiniExcel::Cell::Cell(char d) : data(d), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}

void MiniExcel::insertColumnToLeft() 
{
    // go to top of current column
    Cell* colStart = current;
    while (colStart->up) colStart = colStart->up;

    Cell* oldColCell = colStart;
    Cell* prevNew = nullptr;

    while (oldColCell) {
        Cell* newCell = new Cell();

        // Horizontal links
        newCell->right = oldColCell;
        newCell->left  = oldColCell->left;
        if (oldColCell->left) oldColCell->left->right = newCell;
        oldColCell->left = newCell;

        // Vertical links
        if (prevNew) 
        {
            prevNew->down = newCell;
            newCell->up   = prevNew;
        }

        prevNew = newCell;
        oldColCell = oldColCell->down;
    }

    // If we added column at far left, update topLeft pointer
    if (root->left) {
        root = root->left;
    }

    cols++;
}



void MiniExcel::insertColumnToRight() {
    Cell* colStart = current;
    while (colStart->up) colStart = colStart->up; // go to top row

    Cell* oldColCell = colStart;
    Cell* prevNew = nullptr;

    while (oldColCell) {
        Cell* newCell = new Cell();

        // Horizontal links
        newCell->left = oldColCell;
        newCell->right = oldColCell->right;
        if (oldColCell->right) oldColCell->right->left = newCell;
        oldColCell->right = newCell;

        // Vertical links
        if (prevNew) {
            prevNew->down = newCell;
            newCell->up = prevNew;
        }

        prevNew = newCell;
        oldColCell = oldColCell->down;
    }

    cols++;
}
void MiniExcel::insertRowAbove() {
    // Go to first column of current row
    Cell* rowStart = current;
    while (rowStart->left) rowStart = rowStart->left;

    Cell* oldRowCell = rowStart;
    Cell* prevNew = nullptr;

    while (oldRowCell) {
        Cell* newCell = new Cell();

        // Vertical links
        newCell->down = oldRowCell;
        newCell->up = oldRowCell->up;
        if (oldRowCell->up) oldRowCell->up->down = newCell;
        oldRowCell->up = newCell;

        // Horizontal links
        if (prevNew) {
            prevNew->right = newCell;
            newCell->left = prevNew;
        }

        prevNew = newCell;
        oldRowCell = oldRowCell->right;
    }

    // If we inserted at top row, update root
    if (root->up) root = root->up;

    rows++;
}

void MiniExcel::insertRowBelow() {
    // Go to first column of current row
    Cell* rowStart = current;
    while (rowStart->left) rowStart = rowStart->left;

    Cell* oldRowCell = rowStart;
    Cell* prevNew = nullptr;

    while (oldRowCell) {
        Cell* newCell = new Cell();

        // Vertical links
        newCell->up = oldRowCell;
        newCell->down = oldRowCell->down;
        if (oldRowCell->down) oldRowCell->down->up = newCell;
        oldRowCell->down = newCell;

        // Horizontal links
        if (prevNew) {
            prevNew->right = newCell;
            newCell->left = prevNew;
        }

        prevNew = newCell;
        oldRowCell = oldRowCell->right;
    }

    rows++;
}

void MiniExcel::deleteColumn()
{
    if(current->left != nullptr)
    {
        current->left->right = current->right;
    }
    if(current->right != nullptr)
    {
        current->right->left = current->left;   
    }
    cols--;
    delete current;

}
void MiniExcel::deleteRow()
{   
    if(current->up != nullptr)
    {
        current->up->down = current->down;
    }
    if(current->down != nullptr)
    {
        current->down->up = current->up;   
    }
    rows--;
    delete current;
}
void MiniExcel::clearColumn()
{
    Cell * colptr = current;
    while(colptr)
    {
        colptr = colptr->up;    
    }
    while(colptr != nullptr)
    {
        colptr->data = ' ';
        colptr = colptr->down;
    }
}
void MiniExcel::clearRow()
{
    Cell * rowptr = current;
    while(rowptr)
    {
        rowptr = rowptr->left;
    }
    while(rowptr != nullptr)
    {
        rowptr->data = ' ';
        rowptr = rowptr->right;
    }

}
void MiniExcel::moveUp()
{
   if(current->up != nullptr)
   {
       current = current->up;
   }
}           
void MiniExcel::moveDown()
{
   if(current->down != nullptr)
   {
       current = current->down;
   }
}
void MiniExcel::moveLeft()
{
    if(current->left != nullptr)
    {
        current = current->left;
    }
}
void MiniExcel::moveRight()
{
    if(current->right != nullptr)
    {
        current = current->right;
    }   
}
vector<char> MiniExcel::copy(int startRow, int startCol, int endRow, int endCol)
{
    vector<char> data;
    return data;
}
void MiniExcel::paste(const vector<char>& data, int startRow, int startCol)
{
}   

MiniExcel::~MiniExcel()
{

}