// DataStructureLab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <vector>
#include "header.h"
using namespace std;

KPM Multiplication(KPM&, KPM&);
KPM Addition(KPM&, KPM&);
void Menu(void);
void Calculation(int);
void Output(KPM&, KPM&, KPM&);

int main(void){
	Menu();
	system("pause");
	return 0;
}
KPM Multiplication(KPM& matrix1, KPM& matrix2){

	int row=matrix1.Rows();
	int column=matrix2.Columns();

	if(matrix1.Columns()!=matrix2.Rows()){
		cout<<"WARNING Multiplication(): Matrix1.Row != Matrix2.Columns."<<endl;
		system("pause");
		exit(-1);
	}
	KPM Result(row, column);

	for (int r = 0; r < matrix1.JR.size(); r++) {
		for (int c = 0; c < matrix2.JC.size(); c++) {

			vector<int>columns; 
			vector<int> values1; 

			vector<int> rows;
			vector<int>values2;

			if (matrix1.JR[r] != -1) {
				int next = matrix1.JR[r];
				do {
					int col = -1;
					for (int i = 0; i < matrix1.JC.size(); i++)
						if (matrix1.JC[i] == next)
							col = i;
					if (col == -1) {
						int nextCol = matrix1.NC[next];
						while (nextCol != next) {
							for (int j = 0; j < matrix1.JC.size(); j++)
								if (nextCol == matrix1.JC[j])
									col = j;
							nextCol = matrix1.NC[nextCol];
						}
					}
					values1.push_back(matrix1.AN[next]);
					columns.push_back(col);
					next = matrix1.NR[next];
				} while (next != matrix1.JR[r]);
			}
			
			int val2 = 0;
			int resultVal = 0;
			if (matrix2.JC[c] != -1) {
				int next2 = matrix2.JC[c];
				do {
					int row2 = -1;
					for (int i = 0; i < matrix2.JR.size(); i++)
						if (matrix2.JR[i] == next2) {
							row2 = i; 
						}
					if (row2 == -1) {
						int nextRow = matrix2.NR[next2];
						while (nextRow != next2) {
							for (int j = 0; j < matrix2.JR.size(); j++) {
								if (nextRow == matrix2.JR[j]) {
									row2 = j; val2 = matrix2.AN[next2];
								}
							}
							nextRow = matrix2.NR[nextRow];
						}
					}
					values2.push_back(matrix2.AN[next2]);
					rows.push_back(row2);
					next2 = matrix2.NC[next2];
				} while (next2 != matrix2.JC[c]);

				for (int i1 = 0; i1 < columns.size(); i1++) {
					for (int i2 = 0; i2 < rows.size(); i2++) {
						if (columns[i1] == rows[i2]) {
							resultVal += values1[i1] * values2[i2];
						}
					}
				}

				Result.Add(resultVal, r, c);

			}
		}
	}
	Result.Boxing();
	Result.Reset();
	return Result;
}
KPM Addition(KPM& matrix1, KPM& matrix2) {
	int rows1 = matrix1.Rows();
	int rows2 = matrix2.Rows();
	int columns1 = matrix1.Columns();
	int columns2 = matrix2.Columns();

	if (rows1 != rows2 && columns1 != columns2) {
		cout << "WARNING Addition(): Cannot be excuted Addition function with such matrix sizes." << endl;
		system("pause");
		exit(-1);
	}

	KPM Result(rows1, columns1);

	int* ResValues = new int[Result.Columns()];

	for (int row = 0; row < matrix1.JR.size(); row++) {
		int next1 = matrix1.JR[row];
		int next2 = matrix2.JR[row];

		for (int i = 0; i < Result.Columns(); i++)
			ResValues[i] = 0;

		if (next1 != -1 && next2 != -1) {
			//Finding all values and columns for the first matrix;
			do {
				int col1 = -1;
				for (int i = 0; i < matrix1.JC.size(); i++)
					if (matrix1.JC[i] == next1)
						col1 = i;
				if (col1 == -1) {
					int nextCol1 = matrix1.NC[next1];
					while (nextCol1 != next1) {
						for (int j = 0; j < matrix1.JC.size(); j++)
							if (matrix1.JC[j] == nextCol1)
								col1 = j;
						nextCol1 = matrix1.NC[nextCol1];
					}
				}
				ResValues[col1] += matrix1.AN[next1];
				next1 = matrix1.NR[next1];
			} while (next1 != matrix1.JR[row]);
			do {
				int col2 = -1;
				for (int k = 0; k < matrix2.JC.size(); k++)
					if (matrix2.JC[k] == next2)
						col2 = k;
				if (col2 == -1) {
					int nextCol2 = matrix2.NC[next2];
					while (nextCol2 != next2) {
						for (int z = 0; z < matrix2.JC.size(); z++)
							if (nextCol2 == matrix2.JC[z])
								col2 = z;
						nextCol2 = matrix2.NC[nextCol2];
					}
				}
				ResValues[col2] += matrix2.AN[next2];
				next2 = matrix2.NR[next2];
			} while (next2 != matrix2.JR[row]);

			for (int i = 0; i < Result.Columns(); i++)
				if (ResValues[i] != 0)
					Result.Add(ResValues[i], row, i);
		}
		else if (next1 != -1 && next2 == -1) {
			do {
				int col1 = -1;
				for (int i = 0; i < matrix1.JC.size(); i++)
					if (matrix1.JC[i] == next1)
						col1 = i;
				if (col1 == -1) {
					int nextCol1 = matrix1.NC[next1];
					while (nextCol1 != next1) {
						for (int j = 0; j < matrix1.JC.size(); j++)
							if (matrix1.JC[j] == nextCol1)
								col1 = j;
						nextCol1 = matrix1.NC[nextCol1];
					}
				}
				ResValues[col1] += matrix1.AN[next1];
				next1 = matrix1.NR[next1];
			} while (next1 != matrix1.JR[row]);
			for (int i = 0; i < Result.Columns(); i++)
				if (ResValues[i] != 0)
					Result.Add(ResValues[i], row, i);
		}
		else if (next1 == -1 && next2 != -1) {
			do {
				int col2 = -1;
				for (int k = 0; k < matrix2.JC.size(); k++)
					if (matrix2.JC[k] == next2)
						col2 = k;
				if (col2 == -1) {
					int nextCol2 = matrix2.NC[next2];
					while (nextCol2 != next2) {
						for (int z = 0; z < matrix2.JC.size(); z++)
							if (nextCol2 == matrix2.JC[z])
								col2 = z;
						nextCol2 = matrix2.NC[nextCol2];
					}
				}
				ResValues[col2] += matrix2.AN[next2];
				next2 = matrix2.NR[next2];
			} while (next2 != matrix2.JR[row]);
			for (int i = 0; i < Result.Columns(); i++)
				if (ResValues[i] != 0)
					Result.Add(ResValues[i], row, i);
		}
	}
	delete ResValues;
	Result.Boxing();
	Result.Reset();
	return Result;
}
void Menu(void) {
	int choise;
	system("cls");
	cout << "===================================" << endl;
	cout << "              MENU               " << endl;
	cout << "-----------------------------------" << endl;
	cout << " 1. Generate matrices by hand" << endl;
	cout << " 2. Generate matrices automaticaly" << endl;
	cout << "===================================" << endl;
	cout << "Select an action here: ";
	cin >> choise;
	Calculation(choise);
}
void Calculation(int choise) {
	const int RANGE_VALUE = 10;
	KPM Matrix1; KPM Matrix2;
	char ch;
	int row, column, value;
	double rarefaction;
	system("cls");
	if (choise == 1) {
		cout << "Enter a matrix1 size: ";
		cin >> row >> ch >> column;
		KPM matrix1(row, column);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cout << "Item [" << i << "][" << j << "]: ";
				cin >> value;
				matrix1.Add(value, i, j);
			}
		}
		matrix1.Boxing();
		Matrix1 = matrix1;
		cout << "Enter a matrix2 size: ";
		cin >> row >> ch >> column;
		KPM matrix2(row, column);

		for (int i = 0; i < row; i++) {
			for (int j = 0; j < column; j++) {
				cout << "Item [" << i << "][" << j << "]: ";
				cin >> value;
				matrix2.Add(value, i, j);
			}
		}
		matrix2.Boxing();
		Matrix2 = matrix2;
	}
	else if (choise == 2) {

		//First Matrix generation;

		cout << "Enter a size of matrix1 (e.g. 4x5): ";
		cin >> row >> ch >> column;
		cout << "Define a rarefaction for matrix1: ";
		cin >> rarefaction;
		KPM matrix1(row, column);
		int* values = new int[column];

		//srand(time(0));
		for (int r = 0; r < row; r++) {

			for (int k = 0; k < column; k++)
				values[k] = 0;

			srand(time(NULL));
			int index = 0;
			int val = 0;
			int range = column - (int)(column*(rarefaction));
			int items = rand() %range;
			srand(time(NULL));
			for (int j = 0; j < items; j++) {
				index = rand() % column;
				val = rand() % RANGE_VALUE;
				values[index] = val;
			}
			
			for (int j = 0; j < column; j++)
				if (values[j] != 0)
					matrix1.Add(values[j], r, j);

		}
		matrix1.Boxing();
		//Second Matrix generation;
		cout << "Enter a size of matrix2 (e.g. 4x5): ";
		cin >> row >> ch >> column;
		cout << "Define a rarefaction for matrix2: ";
		cin >> rarefaction;

		KPM matrix2(row, column);
		srand(time(NULL));
		for (int r = 0; r < row; r++) {

			for (int k = 0; k < column; k++)
				values[k] = 0;
			int index = 0;
			int val = 0;
			int items = rand() % (column - (int)(column*(rarefaction)));
			for (int j = 0; j < items; j++) {
				index = rand() % column;
				val = rand() % RANGE_VALUE;
				values[index] = val;
			}
			for (int j = 0; j < column; j++)
				if (values[j] != 0)
					matrix2.Add(values[j], r, j);

		}
		matrix2.Boxing();
		delete values;
		Matrix1 = matrix1; Matrix2 = matrix2;
	}

	system("cls");
	int selection;
	cout << "=============================" << endl;
	cout << "          ACTIONS:           " << endl;
	cout << "-----------------------------" << endl;
	cout << " 1. Add two matrices" << endl;
	cout << " 2. Multiple two matrices" << endl;
	cout << "-----------------------------" << endl;
	cout << "Define an action here: ";
	cin >> selection;

	KPM RESULT;

	if (selection == 1)
		RESULT = Addition(Matrix1, Matrix2);
	else if (selection == 2)
		RESULT = Multiplication(Matrix1, Matrix2);
	RESULT.UnBoxing();
	Output(RESULT, Matrix1, Matrix2);

}
void Output(KPM& result, KPM& matrix1, KPM& matrix2) {
	system("cls");
	cout << "-----------------------------" << endl;
	cout << "\tMatrix1 Boxing: " << endl;
	cout << "-----------------------------"<<endl;
	matrix1.ShowBoxing();
	cout << "-----------------------------" << endl;
	cout << "-----------------------------" << endl;
	cout << "\tMatrix2 Boxing:" << endl;
	cout << "-----------------------------" << endl;
	matrix2.ShowBoxing();
	cout << "-----------------------------" << endl;
	cout << "-----------------------------" << endl;
	cout << "\tRESULT Boxing: " << endl;
	cout << "-----------------------------" << endl;
	result.ShowBoxing();
	cout << "-----------------------------" << endl;
	cout << "\tRESULT Matrix: " << endl;
	result.ShowMatrix();
	cout << "-----------------------------" << endl;
}