#include "Table.h"
#include "Button.h"
Table::Table()
{
	//initTable();
}
Table::~Table()
{
	//delete[] table[];
}

void Table::initTable()
{//clear table
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			table[i][j] = 0;
}

bool Table::isSafe(int row, int col, int val)
{
	return !isSafeRowCol(row, col, val)
		&& !isSafeBox(row - row % 3, col - col % 3, val)
		&& table[row][col] == 0;
}
bool Table::isSafeRowCol(int row, int col, int val)
{
	//row
	for (int col = 0; col < 9; col++)
		if (table[row][col] == val)
			return true;
	//col
	for (int row = 0; row < 9; row++)
		if (table[row][col] == val)
			return true;
	return false;
}
bool Table::isSafeBox(int boxStartRow, int boxStartCol, int val)
{
	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			if (table[row + boxStartRow][col + boxStartCol] == val)
				return true;
	return false;
}
bool Table::emptyBoxes(int& row, int& col)
{
	for (row = 0; row < 9; row++)
		for (col = 0; col < 9; col++)
		{
			if (table[row][col] == 0) return true;
		}
	return false;
}