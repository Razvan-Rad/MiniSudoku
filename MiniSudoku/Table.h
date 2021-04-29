#pragma once

#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Table
{
	void initTable();
	//generating
	int solvedTable[9][9];
	int val[9];
	int tablePos[81];
	int difficultyLevel;
	bool table_status;
public:
	//solving
	bool isSafe(int row, int col, int val);
	bool isSafeRowCol(int row, int col, int val);
	bool isSafeBox(int boxStartRow, int boxStartCol, int val);
	
	bool emptyBoxes(int& row, int& col);
	int table[9][9];

	Table();
	Table(std::string table_str, bool row_major = true);
	void printSudoku();

	//generating
	void createSeed();

	bool solveTable();
	std::string getTable();
	void checkSolvability(int& number);
	void gensudoku();
	bool verifyTableStatus();
	void instantSolve();
	~Table();
};
