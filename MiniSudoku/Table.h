#pragma once
class Table
{
	void initTable();

public:
	bool isSafe(int row, int col, int val);
	bool isSafeRowCol(int row, int col, int val);
	bool isSafeBox(int boxStartRow, int boxStartCol, int val);
	bool emptyBoxes(int& row, int& col);
	int table[9][9] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
					   { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
					   { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
					   { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
					   { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
					   { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
					   { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
					   { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
					   { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };

	Table();
	~Table();
};
