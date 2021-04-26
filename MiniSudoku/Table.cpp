#include "Table.h"
#include "Button.h"
using namespace std;
Table::~Table()
{
	//delete[] table[];
}

int genRandNum(int maxLimit)
{
    return rand() % maxLimit;
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

/////////////////////////////////////////////////////////////////

void Table::createSeed()
{
    solveTable();

    // Saving the solution table
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            solnTable[i][j] = table[i][j];
        }
    }
}


Table::Table()
{

    difficultyLevel = 0;

    for (int i = 0; i < 81; i++)
    {
        tablePos[i] = i;
    }

    random_shuffle(tablePos, (tablePos) + 81, genRandNum);


    for (int i = 0; i < 9; i++)
    {
        val[i] = i + 1;
    }

    random_shuffle(val, (val) + 9, genRandNum);


    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            table[i][j] = 0;
        }
    }

    table_status = true;
}

Table::Table(std::string table_str, bool row_major)
{
    if (table_str.length() != 81)
    {
        table_status = false;
        return;
    }


    for (int i = 0; i < 81; ++i)
    {
        int curr_num = table_str[i] - '0';
        if (!((curr_num == 0) || (curr_num > 0 && curr_num < 10)))
        {
            table_status = false;
            return;
        }

        if (row_major) table[i / 9][i % 9] = curr_num;
        else          table[i % 9][i / 9] = curr_num;
    }


    for (int col_num = 0; col_num < 9; ++col_num)
    {
        bool nums[10] = { false };
        for (int row_num = 0; row_num < 9; ++row_num)
        {
            int curr_num = table[row_num][col_num];
            if (curr_num != 0 && nums[curr_num] == true)
            {
                table_status = false;
                return;
            }
            nums[curr_num] = true;
        }
    }


    for (int row_num = 0; row_num < 9; ++row_num)
    {
        bool nums[10] = { false };
        for (int col_num = 0; col_num < 9; ++col_num)
        {
            int curr_num = table[row_num][col_num];
            if (curr_num != 0 && nums[curr_num] == true)
            {
                table_status = false;
                return;
            }
            nums[curr_num] = true;
        }
    }


    for (int block_num = 0; block_num < 9; ++block_num)
    {
        bool nums[10] = { false };
        for (int cell_num = 0; cell_num < 9; ++cell_num)
        {
            int curr_num = table[((int)(block_num / 3)) * 3 + (cell_num / 3)][((int)(block_num % 3)) * 3 + (cell_num % 3)];
            if (curr_num != 0 && nums[curr_num] == true)
            {
                table_status = false;
                return;
            }
            nums[curr_num] = true;
        }
    }


    for (int i = 0; i < 9; i++)
    {
        val[i] = i + 1;
    }

    random_shuffle(val, (val) + 9, genRandNum);

    table_status = true;
}


bool Table::verifyTableStatus()
{
    return table_status;
}

bool Find0Location(int table[9][9], int& row, int& col)
{
    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            if (table[row][col] == 0)
                return true;
        }
    }

    return false;
}


bool Table::solveTable()
{
    int row, col;


    if (!Find0Location(table, row, col))
        return true; 


    for (int num = 0; num < 9; num++)
    {
  
        if (isSafe(row, col, val[num]))
        {
       
            table[row][col] = val[num];

          
            if (solveTable())
                return true;

           
            table[row][col] = 0;
        }
    }

    return false; 

}

void Table::checkSolvability(int& number)
{
    int row, col;

    if (!Find0Location(table, row, col))
    {
        number++;
        return;
    }


    for (int i = 0; i < 9 && number < 2; i++)
    {
        if (isSafe(row, col, val[i]))
        {
            table[row][col] = val[i];
            checkSolvability(number);
        }

        table[row][col] = 0;
    }

}

void Table::gensudoku()
{
    for (int i = 0; i < 81; i++)
    {
        int x = (tablePos[i]) / 9;
        int y = (tablePos[i]) % 9;
        int temp = table[x][y];
        table[x][y] = 0;

      
        int check = 0;
        checkSolvability(check);
        if (check != 1)
        {
            table[x][y] = temp;
        }
    }
}
void Table::printSudoku()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (table[i][j] == 0)
                cout << ".";
            else
                cout << table[i][j];
            cout << "|";
        }
        cout << endl;
    }

    cout << "\nDifficulty of current sudoku(0 being easiest): " << this->difficultyLevel;
    cout << endl;
}