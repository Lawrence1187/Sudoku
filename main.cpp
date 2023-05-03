//Standard game of sudoku involving a board of 9 x 9 tiles

//Rules are: 
//1. Numbers 1-9, not duplicated, need to all be present in each separate 3x3 square delimited by the double line separators. 
//2. Numbers 1-9, not duplicated, need to also be present in every line and column of the entire board.
//3. Diagonals are not considered in this game to win.

//To build the board, we need to first generate a random configuration of integers on the board that satisfies these rules, save the configuration, 
//then we erase a random number of them (depending on difficulty) and show the user the incomplete board.
//The user then needs to complete the board by entering a number from 1-9 and also indicate which tile he wants to input this number into.
//The program will not be individually checking each input the user enters until all tiles are filled.
//If it matches the random configuration saved previously, then the user wins.
//At any time, the user will be presented with a "reset" option to reset the entire board to its first configuration (as if starting the entire round again)
//At any time, the user can also erase any tiles he deems incorrect, and will be allowed to fill those tiles again.
//The program will track which tiles are filled with a simple boolean.

//Future optional improvements could include a openGL implementation of this program so that the user can directly click where he wants to change the numbers instead of typing in the address of it.

#include <iostream>
#include <cstring>
#include <ctime>
#include <random>
#include <set>
#include <vector>

using std::cout;
using std::endl;
using std::set;
using std::vector;

const int ROWS = 9;
const int COLS = 9;
const int SQR = 9;

void displayBoard(int board[][COLS]) {
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[0][0] << "   |   " << board[0][1] << "   |   " << board[0][2] << "   | |   " << board[0][3] << "   |   " << board[0][4] << "   |   " << board[0][5] << "   | |   " << board[0][6] << "   |   " << board[0][7] << "   |   " << board[0][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[1][0] << "   |   " << board[1][1] << "   |   " << board[1][2] << "   | |   " << board[1][3] << "   |   " << board[1][4] << "   |   " << board[1][5] << "   | |   " << board[1][6] << "   |   " << board[1][7] << "   |   " << board[1][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[2][0] << "   |   " << board[2][1] << "   |   " << board[2][2] << "   | |   " << board[2][3] << "   |   " << board[2][4] << "   |   " << board[2][5] << "   | |   " << board[2][6] << "   |   " << board[2][7] << "   |   " << board[2][8] << "   " << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[3][0] << "   |   " << board[3][1] << "   |   " << board[3][2] << "   | |   " << board[3][3] << "   |   " << board[3][4] << "   |   " << board[3][5] << "   | |   " << board[3][6] << "   |   " << board[3][7] << "   |   " << board[3][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[4][0] << "   |   " << board[4][1] << "   |   " << board[4][2] << "   | |   " << board[4][3] << "   |   " << board[4][4] << "   |   " << board[4][5] << "   | |   " << board[4][6] << "   |   " << board[4][7] << "   |   " << board[4][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[5][0] << "   |   " << board[5][1] << "   |   " << board[5][2] << "   | |   " << board[5][3] << "   |   " << board[5][4] << "   |   " << board[5][5] << "   | |   " << board[5][6] << "   |   " << board[5][7] << "   |   " << board[5][8] << "   " << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[6][0] << "   |   " << board[6][1] << "   |   " << board[6][2] << "   | |   " << board[6][3] << "   |   " << board[6][4] << "   |   " << board[6][5] << "   | |   " << board[6][6] << "   |   " << board[6][7] << "   |   " << board[6][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[7][0] << "   |   " << board[7][1] << "   |   " << board[7][2] << "   | |   " << board[7][3] << "   |   " << board[7][4] << "   |   " << board[7][5] << "   | |   " << board[7][6] << "   |   " << board[7][7] << "   |   " << board[7][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[8][0] << "   |   " << board[8][1] << "   |   " << board[8][2] << "   | |   " << board[8][3] << "   |   " << board[8][4] << "   |   " << board[8][5] << "   | |   " << board[8][6] << "   |   " << board[8][7] << "   |   " << board[8][8] << "   " << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << endl;
}

void createBoard(int board[][COLS]) {
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[0][0] << "   |   " << board[0][1] << "   |   " << board[0][2] << "   | |   " << board[0][3] << "   |   " << board[0][4] << "   |   " << board[0][5] << "   | |   " << board[0][6] << "   |   " << board[0][7] << "   |   " << board[0][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[1][0] << "   |   " << board[1][1] << "   |   " << board[1][2] << "   | |   " << board[1][3] << "   |   " << board[1][4] << "   |   " << board[1][5] << "   | |   " << board[1][6] << "   |   " << board[1][7] << "   |   " << board[1][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[2][0] << "   |   " << board[2][1] << "   |   " << board[2][2] << "   | |   " << board[2][3] << "   |   " << board[2][4] << "   |   " << board[2][5] << "   | |   " << board[2][6] << "   |   " << board[2][7] << "   |   " << board[2][8] << "   " << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[3][0] << "   |   " << board[3][1] << "   |   " << board[3][2] << "   | |   " << board[3][3] << "   |   " << board[3][4] << "   |   " << board[3][5] << "   | |   " << board[3][6] << "   |   " << board[3][7] << "   |   " << board[3][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[4][0] << "   |   " << board[4][1] << "   |   " << board[4][2] << "   | |   " << board[4][3] << "   |   " << board[4][4] << "   |   " << board[4][5] << "   | |   " << board[4][6] << "   |   " << board[4][7] << "   |   " << board[4][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[5][0] << "   |   " << board[5][1] << "   |   " << board[5][2] << "   | |   " << board[5][3] << "   |   " << board[5][4] << "   |   " << board[5][5] << "   | |   " << board[5][6] << "   |   " << board[5][7] << "   |   " << board[5][8] << "   " << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "_______|_______|_______|_|_______|_______|_______|_|_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[6][0] << "   |   " << board[6][1] << "   |   " << board[6][2] << "   | |   " << board[6][3] << "   |   " << board[6][4] << "   |   " << board[6][5] << "   | |   " << board[6][6] << "   |   " << board[6][7] << "   |   " << board[6][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[7][0] << "   |   " << board[7][1] << "   |   " << board[7][2] << "   | |   " << board[7][3] << "   |   " << board[7][4] << "   |   " << board[7][5] << "   | |   " << board[7][6] << "   |   " << board[7][7] << "   |   " << board[7][8] << "   " << endl;
	cout << "_______|_______|_______| |_______|_______|_______| |_______|_______|_______" << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << "   " << board[8][0] << "   |   " << board[8][1] << "   |   " << board[8][2] << "   | |   " << board[8][3] << "   |   " << board[8][4] << "   |   " << board[8][5] << "   | |   " << board[8][6] << "   |   " << board[8][7] << "   |   " << board[8][8] << "   " << endl;
	cout << "       |       |       | |       |       |       | |       |       |       " << endl;
	cout << endl;
}

void displayStartingState(int board[][COLS]) {

}

//j = ROWS, i = COLS
void generateRandomBoard(int board[][COLS]) {
	set<int> checkerSet;
	for (int i = 0; i < COLS; i++) {
		bool uniqueRow = false, uniqueSqr = false;
		while (!uniqueRow || !uniqueSqr) {

			cout << "At column " << i << endl;

			//generate a column of 9 random integers
			vector<int> vectorSet = {1, 2, 3, 4, 5, 6, 7, 8, 9};
			for (int j = 0; j < ROWS; j++) {
				int chosenRand = rand() % vectorSet.size();
				board[j][i] = vectorSet[chosenRand];
				vectorSet.erase(vectorSet.begin() + chosenRand);
				cout << board[j][i] << endl;
			}
			cout << "VectorSet consumed" << endl;

			//check each row for any duplicates among filled elements
			uniqueRow = true;
			uniqueSqr = true;
			if (i > 0) { //since we don't need to check the rows for column 0
				for (int j = 0; j < ROWS; j++) {
					checkerSet.clear();
					for (int k = 0; k <= i; k++) {
						if (board[j][k] != 0) {
							checkerSet.insert(board[j][k]);
						}
					}
					if (checkerSet.size() != i + 1) {
						uniqueRow = false;
						cout << "Test row " << j << " Failed" << endl;
						break;
					}
					cout << "Test row " << j << " Success" << endl;
				}

				//add the elements of the current square to an array
				for (int rowBegin = 0; rowBegin <= 6; rowBegin += 3) {
					int rowEnd = rowBegin + 3;
					checkerSet.clear();
					for (int y = rowBegin; y < rowEnd; y++) {
						for (int x = (i / 3) * 3; x < ((i / 3) * 3) + 3; x++) {
							if (board[y][x] != 0) {
								checkerSet.insert(board[y][x]);
							}
						}
					}
					//check the array for any duplicate with current random element
					if (checkerSet.size() != (i + 1) * 3) {
						uniqueSqr = false;
						cout << "Test squares Failed" << endl;
						break;
					}
					cout << "Test squares Success" << endl;
				}
			}
		}
		displayBoard(board);
	}
}

int main(void) {
	srand(time(NULL));
	cout << "Welcome to Sudoku!" << endl;
	int board[9][9];
	memset(board, 0, sizeof(board)); //function from cstring that fills the entire board with 0.

	generateRandomBoard(board);
	displayBoard(board);
	cout << "Test board generator end.";

	displayStartingState(board);

	//Try using a 2D array.
	return 0;
}