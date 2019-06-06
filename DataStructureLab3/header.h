#include "stdafx.h"
#include <iostream>
#include <vector>
#ifndef HEADER_H
#define HEADER_H
using namespace std;

class KPM{
private:
	int rows;
	int columns;
	int** Matrix;
public:
	vector<int> AN;
	vector<int> NR;
	vector<int> NC;
	vector<int> JR;
	vector<int> JC;

	KPM();
	KPM(int, int);
	KPM(const KPM&);
	KPM& operator=(const KPM&);
	void Add(int, int, int);
	void Boxing(void);
	void UnBoxing(void);
	void Reset(void) {
		if (Matrix != nullptr) {
			for (int i = 0; i < rows; i++)
				delete Matrix[i];
			delete Matrix;
		}
		rows = 0; columns = 0;
		Matrix = nullptr;
	}
	int Rows(void){
		return rows;
	}
	int Columns(void){
		return columns;
	}
	void ShowMatrix(void);
	void ShowBoxing(void);
	~KPM(){
		if(Matrix!=nullptr){
			for(int i=0; i<rows; i++)
				delete Matrix[i];
			delete Matrix;
		}
	}
};


#endif