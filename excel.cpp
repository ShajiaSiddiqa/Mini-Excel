#include "excel.hpp"

MiniExcel::Cell::Cell(char d) : data(d), up(nullptr), down(nullptr), left(nullptr), right(nullptr)
{
}

void MiniExcel::insertColumnToLeft()
{

}

void MiniExcel::insertColumnToRight()
{

}
void MiniExcel::insertRowAbove()
{

}   
void MiniExcel::insertRowBelow()
{

}
void MiniExcel::deleteColumn()
{

}
void MiniExcel::deleteRow()
{   
    
}
void MiniExcel::clearColumn()
{

}
void MiniExcel::clearRow()
{
}
void MiniExcel::moveUp()
{
}           
void MiniExcel::moveDown()
{
}
void MiniExcel::moveLeft()
{
}
void MiniExcel::moveRight()
{       
}
vector<char> MiniExcel::copy(int startRow, int startCol, int endRow, int endCol)
{
    vector<char> data;
    return data;
}
void MiniExcel::paste(const vector<char>& data, int startRow, int startCol)
{
}   

MiniExcel::MiniExcel()
{

}

MiniExcel::~MiniExcel()
{

}