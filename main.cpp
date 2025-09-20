#include <iostream>
#include "excel.hpp"
using namespace std;

int main() {
    MiniExcel excel;

    cout << "Initial sheet:\n";
    excel.printSheet();

    cout << "\n--- Interactive Mode ---\n";
    cout << "Use w (up), s (down), a (left), d (right), q (quit)\n";

    char cmd;
    while (true) 
    {
        // clear screen before printing
      
        system("clear"); 

        excel.printSheet();
        cout << "Enter command (w/a/s/d/r/c/u/v to move, q to quit): ";
        cin >> cmd;

        if (cmd == 'q') break;
        else if (cmd == 'w') excel.moveUp();
        else if (cmd == 's') excel.moveDown();
        else if (cmd == 'a') excel.moveLeft();
        else if (cmd == 'd') excel.moveRight();
        else if (cmd == 'v') excel.insertRowBelow();
        else if (cmd == 'u') excel.insertRowAbove();
        else if (cmd == 'l') excel.insertColumnToLeft();
        else if (cmd == 'r') excel.insertColumnToRight();

        else cout << "Invalid command!\n";
    }

    return 0;
}
