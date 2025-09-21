#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <string>
#include "excel.hpp"
#include <vector>
using namespace std;  

// RAII to set terminal raw and restore on exit
struct RawTerm 
{
    struct termios orig;
    RawTerm() 
    {
        tcgetattr(STDIN_FILENO, &orig);
        struct termios raw = orig;
        raw.c_lflag &= ~(ICANON | ECHO); // turn off canonical mode & echo
        raw.c_cc[VMIN] = 1;   // read() returns after 1 byte
        raw.c_cc[VTIME] = 0;
        tcsetattr(STDIN_FILENO, TCSANOW, &raw);
    }
    ~RawTerm() {
        tcsetattr(STDIN_FILENO, TCSANOW, &orig);
    }
};

// Read one key (handles escape sequences for arrows/modifiers)
int readKey()
{
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) != 1) return -1;

    if (c == 27) { // ESC - possible arrow sequence
        unsigned char seq1;
        if (read(STDIN_FILENO, &seq1, 1) != 1) return 27;
        if (seq1 == '[') {
            unsigned char seq2;
            if (read(STDIN_FILENO, &seq2, 1) != 1) return 27;

            // Simple arrows: ESC [ A/B/C/D
            if (seq2 == 'A') return 1000 + 1; // UP
            if (seq2 == 'B') return 1000 + 2; // DOWN
            if (seq2 == 'C') return 1000 + 3; // RIGHT
            if (seq2 == 'D') return 1000 + 4; // LEFT

            // Extended sequences (e.g. ESC [ 1 ; 2 A ) => Shift+Arrow
            // seq2 may be '1' or other digit. Read until final letter (A-D)
            string mid;
            mid.push_back((char)seq2);
            unsigned char ch;
            while (read(STDIN_FILENO, &ch, 1) == 1) {
                if ( (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ) {
                    char arrow = ch;
                    // check if mid contains ";2" which typically indicates Shift
                    if (mid.find(";2") != string::npos) {
                        switch (arrow) {
                            case 'A': return 2000 + 1; // Shift+Up
                            case 'B': return 2000 + 2; // Shift+Down
                            case 'C': return 2000 + 3; // Shift+Right
                            case 'D': return 2000 + 4; // Shift+Left
                        }
                    } else {
                        // other modifiers (Ctrl/Alt) - treat as plain arrow
                        switch (arrow) {
                            case 'A': return 1000 + 1;
                            case 'B': return 1000 + 2;
                            case 'C': return 1000 + 3;
                            case 'D': return 1000 + 4;
                        }
                    }
                    break;
                } else {
                    mid.push_back((char)ch);
                    // continue reading
                }
            }
            return 27;
        } else if (seq1 == 'O') {
            // Some terminals use ESC O A/B/C/D
            unsigned char seq2;
            if (read(STDIN_FILENO, &seq2, 1) != 1) return 27;
            if (seq2 == 'A') return 1000 + 1;
            if (seq2 == 'B') return 1000 + 2;
            if (seq2 == 'C') return 1000 + 3;
            if (seq2 == 'D') return 1000 + 4;
        }
        return 27;
    }
    // normal printable characters
    return (int)c;
}

int main() 
{
    MiniExcel excel;             
    RawTerm rt;                    // enables raw terminal mode
    bool running = true;

    vector<char> clipboard;  

    while (running) 
    {
        system("clear");
        excel.printSheet();
        cout << "\nControls:\n";
        cout << "  Arrow keys = move\n";
        cout << "  Shift+Arrow = insert row/column\n";
        cout << "  a = delete column, w = delete row\n";
        cout << "  s = clear row, d = clear column\n";
        cout << "  e = edit current cell\n";
        cout << "  c = copy selection, v = paste\n";
        cout << "  q = quit\n";

        int k = readKey();

        if (k == -1) continue;

        if (k >= 2000) 
        {   // Shift + Arrow
            int code = k - 2000;
            switch (code) 
            {
                case 1: excel.insertRowAbove(); break;      // Shift+Up
                case 2: excel.insertRowBelow(); break;      // Shift+Down
                case 3: excel.insertColumnToRight(); break; // Shift+Right
                case 4: excel.insertColumnToLeft(); break;  // Shift+Left
            }
        } 
        else if (k >= 1000) 
        {   // Arrow keys
            int code = k - 1000;
            switch (code) 
            {
                case 1: excel.moveUp(); break;
                case 2: excel.moveDown(); break;
                case 3: excel.moveRight(); break;
                case 4: excel.moveLeft(); break;
            }
        } 
        else 
        {
            if (k == 'q' || k == 'Q') 
            {
                running = false;
            } 
            else if (k == 'e' || k == 'E') 
            {
                string val;
                cout << "\nEnter value for current cell: ";
                cin >> val;
                excel.setData(val);
            } 
            else if (k == 'a') 
            {
                excel.deleteColumn();
            } 
            else if (k == 'w') 
            {
                excel.deleteRow();
            }
            else if (k == 'd') 
            {
                excel.clearColumn();
            } 
            else if (k == 's') 
            {
                excel.clearRow();
            } 
            else if (k == 'c' || k == 'C') 
            {
                // for now copy only current cell
                int r = excel.getRowIndex(excel.current);
                int c = excel.getColIndex(excel.current);
                clipboard = excel.copy(r, c, r, c);  
                cout << "\nCopied cell (" << r << "," << c << ")\n";
                cin.get(); 
            } 
            else if (k == 'v' || k == 'V') 
            {
                if (!clipboard.empty()) 
                {
                    int r = excel.getRowIndex(excel.current);
                    int c = excel.getColIndex(excel.current);
                    excel.paste(clipboard, r, c);
                    cout << "\nPasted into (" << r << "," << c << ")\n";
                    cin.get(); 
                }
            }
        }
    }

    return 0;
}

//   a -> for delete column                                              
//   w -> for delete row                             
//   s -> clear row                             
//   d -> clear column                             
//   e -> for edit current cell                             
//   q -> for quit the program                             
//   Arrow keys to move                             
//   Shift + Arrow keys to insert row/column                             
//   c -> copy                             
//   v -> paste                             