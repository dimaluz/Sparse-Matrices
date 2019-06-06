#include "stdafx.h"
#include <iostream>
#include "header.h"
using namespace std;

KPM::KPM(){
	Matrix=nullptr;
	rows=0; columns=0;
}
KPM::KPM(int row, int col){
	rows=row; columns=col;
	Matrix=new int*[rows];
	for(int i=0; i<rows; i++)
		Matrix[i]=new int[columns];
	for(int i=0; i<rows; i++)
		for(int j=0; j<columns; j++)
			Matrix[i][j]=0;
}
KPM::KPM(const KPM& other){
	rows=other.rows; columns=other.columns;
	Matrix=new int*[rows];
		if(other.Matrix!=nullptr){
		for(int i=0; i<rows; i++)
			Matrix[i]=new int[columns];
		for(int i=0; i<rows; i++)
			for(int j=0; j<columns; j++)
				Matrix[i][j]=other.Matrix[i][j];
	}
	AN=other.AN; NC=other.NC; NR=other.NR; JC=other.JC; JR=other.JR;
}
KPM& KPM::operator=(const KPM& other){
	if(this==&other)
		return *this;

	if(Matrix!=nullptr){
		for(int i=0; i<rows; i++)
			delete Matrix[i];
		delete Matrix;
	}

	rows=other.rows; columns=other.columns;
	Matrix=new int*[rows];
	for(int i=0; i<rows; i++)
		Matrix[i]=new int[columns];

	for(int i=0; i<rows; i++)
		for(int j=0; j<columns; j++)
			Matrix[i][j]=other.Matrix[i][j];

	AN=other.AN; NR=other.NR; NC=other.NC; JC=other.JC; JR=other.JR;
	return *this;
}
void KPM::Add(int value, int row, int column){
	if(Matrix!=nullptr)
		Matrix[row][column]=value;
}
void KPM::Boxing(void){
	bool FindFirstItem;
	int* tempAN; int* tempNC; int* tempJC;
	int* tempIA; int* tempJA;


	for(int i=0; i<rows; i++){
		FindFirstItem=false;
		for(int j=0; j<columns; j++){
			if(Matrix[i][j]!=0){
				AN.push_back(Matrix[i][j]);
				if(!FindFirstItem){
					JR.push_back(AN.size()-1);
					FindFirstItem=true;
				}
				else if(FindFirstItem){
					NR.push_back(AN.size()-1);
				}
			}
		}
		if(FindFirstItem)
			NR.push_back(JR[i]);
		else
			JR.push_back(-1);
	}

	tempAN=new int[AN.size()];
	tempNC=new int[AN.size()];
	tempJC=new int[columns];

	tempIA=new int[AN.size()];
	tempJA=new int[AN.size()];

	for(int i=0; i<columns; i++)
		tempJC[i]=-1;

	int ANIndex=0, JCIndex=0;

	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(Matrix[i][j]!=0){
				tempAN[ANIndex]=Matrix[i][j];
				if(tempJC[j]==-1)
					tempJC[j]=ANIndex;
				ANIndex++;
			}
		}
	}
	for(int i=0; i<columns; i++)
		JC.push_back(tempJC[i]);

	//Coordinate writing
	int Index=0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if(Matrix[i][j]!=0){
				tempIA[Index]=i;
				tempJA[Index]=j;
				Index++;
			}
		}
	}
	//NC;
	for(int i=0; i<AN.size(); i++)
		tempNC[i]=-1;

	FindFirstItem=false;
	int IndexInNC=0; int NextIndex=0; int IndexFirst=0; //int CuurentIndex=0;
	int size=AN.size();

	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			FindFirstItem=false;
			if(Matrix[i][j]!=0){
				if(!FindFirstItem){
					FindFirstItem=true;
					for(int z=0; z<size; z++)
						if(tempIA[z]==i && tempJA[z]==j)
							IndexFirst=z;
					IndexInNC=IndexFirst;
					NextIndex=IndexFirst+1;
				}
				for(int k=NextIndex; k<size; k++){
					if(tempJA[k]==j && tempNC[IndexInNC]==-1){
						tempNC[IndexInNC]=k;
						IndexInNC=k;
					}
				}
				if(tempNC[IndexInNC]==-1)
					tempNC[IndexInNC]=IndexFirst;
				
			}
		}
	}
	
	for(int i=0; i<size; i++)
		NC.push_back(tempNC[i]);


	delete tempAN; delete tempNC; delete tempJC; delete tempJA; delete tempIA;  
}
void KPM::UnBoxing(void){
	if(Matrix!=nullptr){
		for(int i=0; i<rows; i++)
			delete Matrix[i];
		delete Matrix;
	}

	rows=JR.size(); columns=JC.size();
	Matrix=new int*[rows];
	for(int i=0; i<rows; i++)
		Matrix[i]=new int[columns];

	for(int i=0; i<rows; i++)
		for(int j=0; j<columns; j++)
			Matrix[i][j]=0;


	//Items searching;
	int ItemRow=-1, ItemCol=-1; 
	int IndexAN=-1;
	int value=0; 
	int NextCol=-1; 
	int NextRow=-1;

	for(int i=0; i<AN.size(); i++){
		ItemRow=-1; ItemCol=-1;

		value=AN[i];

		for(int r=0; r<JR.size(); r++)
			if(JR[r]==i)
				ItemRow=r;
		for(int c=0; c<JC.size(); c++)
			if(JC[c]==i)
				ItemCol=c;

		if(ItemRow==-1){
			NextRow=NR[i];
			while(NextRow!=i){
				for(int r=0; r<JR.size(); r++)
					if(JR[r]==NextRow)
						ItemRow=r;
				NextRow=NR[NextRow];
			}
		}
		if(ItemCol==-1){
			NextCol=NC[i];
			while(NextCol!=i){
				for(int c=0; c<JC.size(); c++)
					if(JC[c]==NextCol)
						ItemCol=c;
				NextCol=NC[NextCol];
			}
		}
		if(ItemRow!=-1 && ItemCol!=-1)
			Matrix[ItemRow][ItemCol]=value;
	}
}
void KPM::ShowMatrix(void) {
	//cout << "-------------------------" << endl;
	cout << "SIZE (" << rows << "x" << columns << ")" << endl;
	if (Matrix != nullptr) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++)
				cout << Matrix[i][j] << " ";
			cout << endl;
		}
	}
	//cout << "-------------------------" << endl;
}
void KPM::ShowBoxing(void){
	//cout << "----------------------------" << endl;
	//cout << "Boxing Matrix:" << endl;
	cout<<"AN: [ ";
	for(int i=0 ;i<AN.size(); i++)
		cout<<AN[i]<<" ";
	cout<<"]"<<endl;
	cout<<"NR: [";
	for(int i=0; i<NR.size(); i++)
		cout<<NR[i]<<" ";
	cout<<"]"<<endl;
	cout<<"NC: [ ";
	for(int i=0; i<NC.size(); i++)
		cout<<NC[i]<<" ";
	cout<<"]"<<endl;
	cout<<"JR: [ ";
	for(int i=0; i<JR.size(); i++)
		cout<<JR[i]<<" ";
	cout<<"]"<<endl;
	cout<<"JC: [ ";
	for(int i=0; i<JC.size(); i++)
		cout<<JC[i]<<" ";
	cout<<"]"<<endl;
	//cout << "----------------------------" << endl;
}
