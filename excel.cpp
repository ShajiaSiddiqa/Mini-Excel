#include "excel.hpp"


MiniExcel::MiniExcel() {
    rows = 5;
    cols = 5;

    root = new Cell(" ");
    current = root;

    // ----------- first row
    Cell* rowStart = root;
    for (int c = 1; c < cols; c++) 
    {
        Cell* newCell = new Cell(" ");
        rowStart->right = newCell;
        newCell->left = rowStart;
        rowStart = newCell;
    }

    // ---------- remaining rows
    Cell* aboveRow = root;
    for (int r = 1; r < rows; r++) 
    {
        Cell* newRowStart = new Cell(" ");
        aboveRow->down = newRowStart;
        newRowStart->up = aboveRow;

        // --------- Filling rest of row
        Cell* leftCell = newRowStart;
        Cell* aboveCell = aboveRow->right;

        for (int c = 1; c < cols; c++) 
        {
            Cell* newCell = new Cell( " ");
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

MiniExcel::Cell::Cell(string d) : data(d), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}

void MiniExcel::insertColumnToLeft() 
{
    // go to top of current column
    Cell* colStart = current;
    while (colStart->up) colStart = colStart->up;

    Cell* oldColCell = colStart;
    Cell* prevNew = nullptr;

    while (oldColCell) 
    {
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

    // if (current == root) root = root->left;
    if (colStart == root) 
    {
        root = root->left;
    }

    cols++;
}



void MiniExcel::insertColumnToRight() 
{
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
void MiniExcel::insertRowAbove() 
{
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

    // if (current == root) root = root->up;
    if (rowStart == root) 
    {
        root = root->up;
    }

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
    // Go to top of current column
    Cell* colStart = current;
    while (colStart->up) colStart = colStart->up;

    Cell* rowPtr = colStart;
    Cell* nextCol = current->right ? current->right : current->left;

    while (rowPtr) 
    {
        Cell* toDelete = rowPtr;
        rowPtr = rowPtr->down;

        // Fix horizontal links
        if (toDelete->left) toDelete->left->right = toDelete->right;
        if (toDelete->right) toDelete->right->left = toDelete->left;

        delete toDelete;
    }

    cols--;

    current = nextCol;
}

void MiniExcel::deleteRow() 
{
    Cell* rowStart = current;
    while (rowStart->left) rowStart = rowStart->left;

    Cell* colPtr = rowStart;
    Cell* nextRow = current->down ? current->down : current->up;

    while (colPtr) 
    {
        Cell* toDelete = colPtr;
        colPtr = colPtr->right;

        if (toDelete->up) toDelete->up->down = toDelete->down;
        if (toDelete->down) toDelete->down->up = toDelete->up;

        delete toDelete;
    }

    rows--;

    current = nextRow;
}

void MiniExcel::clearColumn() 
{
    // Go to the top of the current column
    Cell* colPtr = current;
    while (colPtr->up) colPtr = colPtr->up;

    // Clear downward
    while (colPtr) {
        colPtr->data = ' ';
        colPtr = colPtr->down;
    }
}

void MiniExcel::clearRow() {
    // Go to leftmost cell of current row
    Cell* rowPtr = current;
    while (rowPtr->left) rowPtr = rowPtr->left;

    // Clear entire row
    while (rowPtr) {
        rowPtr->data = ' ';
        rowPtr = rowPtr->right;
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

MiniExcel::~MiniExcel()
{

}

int MiniExcel::getRowIndex(Cell* target) {
    int row = 0;
    Cell* rowPtr = root;
    while (rowPtr) {
        Cell* colPtr = rowPtr;
        while (colPtr) {
            if (colPtr == target) return row;
            colPtr = colPtr->right;
        }
        rowPtr = rowPtr->down;
        row++;
    }
    return -1; // not found
}

int MiniExcel::getColIndex(Cell* target) {
    int col = 0;
    Cell* rowPtr = root;
    while (rowPtr) {
        Cell* colPtr = rowPtr;
        col = 0;
        while (colPtr) {
            if (colPtr == target) return col;
            colPtr = colPtr->right;
            col++;
        }
        rowPtr = rowPtr->down;
    }
    return -1; // not found
}

void MiniExcel:: setData(const string& value) 
{
    current->data = value;
}

 string MiniExcel::getData() const 
{
    return current->data;
}

void MiniExcel::editCurrentCell()
{
    int r = getRowIndex(current);
    int c = getColIndex(current);
    cout << "Editing cell (" << r << "," << c << "): ";
    string value;
    cin >> value;
    current->data = value;  
}

const int MAX_VISIBLE_ROWS = 17;

void MiniExcel::printSheet() 
{
    int startRow = 0;
    int curRow = 0;

    // ------------ Finding current row index
    Cell* temp = root;
    while (temp && temp != current) 
    {
        Cell* rowPtr = temp;
        int c = 0;
        while (rowPtr && rowPtr != current) 
        {
            rowPtr = rowPtr->right;
            c++;
        }
        if (rowPtr == current) break;
        temp = temp->down;
        curRow++;
    }

    // Sliding window: if current row is beyond visible range, shifting startRow
    if (curRow >= MAX_VISIBLE_ROWS) 
    {
        startRow = curRow - MAX_VISIBLE_ROWS + 1;
    }

    int endRow = min(startRow + MAX_VISIBLE_ROWS, rows);

    // Print column headers (A, B, C, ...)
    cout << "    ";
    for (int c = 0; c < cols; c++) {
        cout << "   " << char('A' + c) << "     ";
    }
    cout << "\n";

    // Navigate to startRow
    Cell* rowPtr = root;
    for (int r = 0; r < startRow; r++) 
        {
            rowPtr = rowPtr->down;
        }

    // Print only window rows
    for (int r = startRow; r < endRow; r++)
    {
        // --------- Top/border of row
        for (int c = 0; c < cols; c++) {
            if (c == 0) 
                cout << (r == startRow ? "    ┌" : "    ├");
            for (int i = 0; i < 8; i++) 
                cout << "─";
            cout << (c == cols - 1 ? (r == startRow ? "┐" : "┤") : (r == startRow ? "┬" : "┼"));
        }
        cout << "\n";

        // ---------- Row label (1,2,3,... )
        if (r + 1 < 100)
            cout << setw(2) << r + 1 << "  ";
        else
            cout << setw(2) << r + 1 << " ";

        // ------------- Cursor position and Cell content
        Cell* colPtr = rowPtr;
        for (int c = 0; c < cols; c++) 
        {
            cout << "│";
            if (colPtr == current) 
            {
                cout << "\033[34m";  // blue
                cout << setw(8) << left << (colPtr->data + "|");
                cout << "\033[0m";
            } else 
            {
                cout << setw(8) << left << colPtr->data;
            }
            colPtr = colPtr->right;
            if (c == cols - 1) cout << "│";
        }
        cout << "\n";

        // Go down for next row
        rowPtr = rowPtr->down;
    }

    // Bottom border for window
    for (int c = 0; c < cols; c++) 
    {
        if (c == 0)
            cout << "    └";
        for (int i = 0; i < 8; i++) 
            cout << "─";
        cout << (c == cols - 1 ? "┘" : "┴");
    }
    cout << "\n";
}

vector<char> MiniExcel::copy(int startRow, int startCol, int endRow, int endCol) 
{
    vector<char> buffer;

    if (startRow > endRow) swap(startRow, endRow);
    if (startCol > endCol) swap(startCol, endCol);

    Cell* rowPtr = root;

    // ------------ move to startRow
    for (int r = 0; r < startRow && rowPtr; r++) 
    {
        rowPtr = rowPtr->down;
    }

    for (int r = startRow; r <= endRow && rowPtr; r++) 
    {
        Cell* colPtr = rowPtr;

        // ------------ move to startCol
        for (int c = 0; c < startCol && colPtr; c++) 
        {
            colPtr = colPtr->right;
        }

        for (int c = startCol; c <= endCol && colPtr; c++) 
        {
           
            for (char ch : colPtr->data) 
            {
                buffer.push_back(ch);
            }
            buffer.push_back('\t'); // as a delimiter between cells
            colPtr = colPtr->right;
        }

        buffer.push_back('\n'); // das a delimiter between rows
        rowPtr = rowPtr->down;
    }

    return buffer;
}

void MiniExcel::paste(const vector<char>& data, int startRow, int startCol) 
{
    Cell* rowPtr = root;

    // ------------ move to startRow
    for (int r = 0; r < startRow && rowPtr; r++) {
        rowPtr = rowPtr->down;
    }

    int r = startRow, c = startCol;
    string cellContent;

    for (char ch : data) 
    {
        if (ch == '\t' || ch == '\n') 
        {   
            Cell* colPtr = rowPtr;
            for (int i = 0; i < c && colPtr; i++) 
            {
                colPtr = colPtr->right;
            }
            if (colPtr) colPtr->data = cellContent;

            cellContent.clear();

            if (ch == '\t') 
            {
                c++;
            } else if (ch == '\n') 
            {
                r++;
                c = startCol;
                if (rowPtr) rowPtr = rowPtr->down;
            }
        }
        else 
        {
            cellContent.push_back(ch);
        }
    }
}
